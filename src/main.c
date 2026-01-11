#include "main.h"

#if (RUN_BSP_TEST_CASE)
extern void bsp_run_test(void);
#endif

int main(void) {
    while (1) 
    {

    }
    return 0;
}

// arm-none-eabi-gcc -c -mcpu=cortex-m3 -mthumb main.c -o main.o
// To use malloc function, add --specs=nano.specs in linking flag