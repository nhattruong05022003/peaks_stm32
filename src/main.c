#include "main.h"

#if (RUN_BSP_TEST_CASE)
extern void bsp_run_test(void);
#endif

#if (RUN_DMA_TEST_CASE)
extern void dma_run_test(void);
#endif

#if (RUN_SPI_TEST_CASE)
extern void spi_run_test(void);
#endif

int main(void) {

#if (RUN_BSP_TEST_CASE)
    bsp_run_test();
#endif

#if (RUN_DMA_TEST_CASE)
    dma_run_test();
#endif

#if (RUN_SPI_TEST_CASE)
    spi_run_test();
#endif

#if (BLINKY_CONFIRM_TEST_PASS)
    BSP_IO_Configurate(BSP_IO_PORTC_PIN_13, BSP_IO_CONFIG_OUTPUT_GPIO_PUSH_PULL | BSP_IO_MODE_OUTPUT_50MHZ | BSP_IO_OUTPUT_INIT_STATE_HIGH);
#endif
    while (1) 
    {
#if (BLINKY_CONFIRM_TEST_PASS)
        BSP_IO_Toggle(BSP_IO_PORTC_PIN_13); // Toggle PC13
        BSP_Software_Delay(BSP_DELAY_UNIT_MILLISECOND, 500);
#endif
    }
    return 0;
}

// arm-none-eabi-gcc -c -mcpu=cortex-m3 -mthumb main.c -o main.o
// To use malloc function, add --specs=nano.specs in linking flag
// make -j4 CHIP=STM32F103C8
