CC=arm-none-eabi-gcc.exe
OBJCOPY=arm-none-eabi-objcopy.exe
SIZE = arm-none-eabi-size.exe
MACH=cortex-m3
CFLAGS=-c -mcpu=$(MACH) -mthumb -std=gnu17 -Wall -Wextra -O0 $(INCLUDE)
LDFLAGS= -mcpu=$(MACH) -mthumb --specs=nano.specs -L$(SRC_DIR) -T $(SRC_DIR)/stm32_ls.ld  $(SRC_DIR)/memory_regions.ld -Wl,-Map=$(OUTPUT_DIR)/final.map

SRC_DIR=src
LIB_DIR=lib

BSP_DIR=bsp
BSP_ALL_DIR=bsp/all
BSP_TEST_DIR=bsp/!test

ifeq ($(CHIP), STM32F103C8)
BSP_SPECIFIC_DEVICE_DIR=bsp/mcu/stm32f1xx/stm32f103
BSP_DEVICE_DIR=bsp/mcu/stm32f1xx
else ifeq ($(CHIP), STM32F103CB)
BSP_SPECIFIC_DEVICE_DIR=bsp/mcu/stm32f1xx/stm32f103
BSP_DEVICE_DIR=bsp/mcu/stm32f1xx
endif

DMA_DIR=dma
DMA_TEST_DIR=dma/!test

SPI_DIR=spi
SPI_TEST_DIR=spi/!test

INCLUDE= -I$(BSP_DIR) -I$(BSP_ALL_DIR) -I$(BSP_TEST_DIR) -I$(BSP_DEVICE_DIR) -I$(BSP_SPECIFIC_DEVICE_DIR) -I$(LIB_DIR) -I$(SRC_DIR) \
			-I$(DMA_DIR) -I$(DMA_TEST_DIR) \
			-I$(SPI_DIR) -I$(SPI_TEST_DIR)

OUTPUT_DIR=Debug

# List all directories containing source files
SRC_DIRS = . $(BSP_DIR) $(BSP_ALL_DIR) $(BSP_TEST_DIR) $(BSP_DEVICE_DIR) $(BSP_SPECIFIC_DEVICE_DIR) $(LIB_DIR) $(SRC_DIR) \
				$(DMA_DIR) $(DMA_TEST_DIR) \
				$(SPI_DIR) $(SPI_TEST_DIR)
vpath %.c $(SRC_DIRS)

# Find all .c files in those directories
SOURCES = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))

# Convert source file names to object file names in the OUTPUT_DIR
# Example: bsp/bsp_io.c -> Debug/bsp_io.o
OBJECTS = $(addprefix $(OUTPUT_DIR)/, $(notdir $(SOURCES:.c=.o)))

TARGET_ELF=$(OUTPUT_DIR)/final.elf
TARGET_HEX=$(OUTPUT_DIR)/final.hex
TARGET_BIN=$(OUTPUT_DIR)/final.bin

# The 'all' target now depends on the files in the output directory
all: $(TARGET_ELF) $(TARGET_HEX) $(TARGET_BIN)
	@echo "--- Size Information ---"
	$(SIZE) $(TARGET_ELF)

# Pattern Rule for object files (More concise than individual rules)
# This rule handles all source files
$(OUTPUT_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

# Linking target
$(TARGET_ELF): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

# Post-build targets
$(TARGET_HEX): $(TARGET_ELF)
	$(OBJCOPY) -O ihex $< $@

$(TARGET_BIN): $(TARGET_ELF)
	$(OBJCOPY) -O binary $< $@

clean:
	rm Debug/*