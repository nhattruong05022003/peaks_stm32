#include "main.h"

#if (RUN_BSP_TEST_CASE)
extern void bsp_run_test(void);
#endif

#if (RUN_DMA_TEST_CASE)
extern void dma_run_test(void);
#endif

int main(void) {

#if (RUN_BSP_TEST_CASE)
    bsp_run_test();
#endif

#if (RUN_DMA_TEST_CASE)
    dma_run_test();
#endif

    while (1) 
    {

    }
    return 0;
}

// arm-none-eabi-gcc -c -mcpu=cortex-m3 -mthumb main.c -o main.o
// To use malloc function, add --specs=nano.specs in linking flag