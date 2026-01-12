#include "main.h"

#if (RUN_BSP_TEST_CASE)

void abort(void)
{
    while(1)
    {
        __asm__ volatile("nop");
    }
}

void bsp_ioport_test_case(void)
{
    BSP_IO_Configurate(BSP_IO_PORTA_PIN_0, BSP_IO_CONFIG_OUTPUT_GPIO_PUSH_PULL | BSP_IO_MODE_OUTPUT_50MHZ | BSP_IO_OUTPUT_INIT_STATE_HIGH);
    BSP_IO_Configurate(BSP_IO_PORTA_PIN_1, BSP_IO_CONFIG_INPUT_PULL_UP_DOWN | BSP_IO_INPUT_PULL_MODE_PULLHIGH);
    ASSERT((GPIOA->CRL & 0x0F) == (BSP_IO_CONFIG_OUTPUT_GPIO_PUSH_PULL | BSP_IO_MODE_OUTPUT_50MHZ));
    BSP_IO_Write(BSP_IO_PORTA_PIN_0, BSP_IO_STATE_LOW);
    ASSERT((GPIOA->ODR & 0x01) == BSP_IO_STATE_LOW);
    ASSERT(BSP_IO_Read(BSP_IO_PORTA_PIN_1) == BSP_IO_STATE_LOW);
    BSP_IO_Write(BSP_IO_PORTA_PIN_0, BSP_IO_STATE_HIGH);
    ASSERT((GPIOA->ODR & 0x01) == BSP_IO_STATE_HIGH);
    ASSERT(BSP_IO_Read(BSP_IO_PORTA_PIN_1) == BSP_IO_STATE_HIGH);
    BSP_IO_Toggle(BSP_IO_PORTA_PIN_0);
    ASSERT((GPIOA->ODR & 0x01) == BSP_IO_STATE_LOW);
    ASSERT(BSP_IO_Read(BSP_IO_PORTA_PIN_1) == BSP_IO_STATE_LOW);
}
#if (BSP_HEAP_SIZE > 0)

#define BSP_MALLOC_TEST_LENGTH 64U

void bsp_heap_test_case(void)
{
    uint8_t i = 0U;
    uint8_t *p_malloc;
    uint8_t *p_malloc_1;
    
    /* Test case 1: Malloc */
    p_malloc = malloc(BSP_MALLOC_TEST_LENGTH);
    ASSERT(p_malloc != NULL);

    for(i = 0U; i < BSP_MALLOC_TEST_LENGTH; i++)
    {
        p_malloc[i] = i;
    }

    free(p_malloc);

    /* Test case 1: Calloc */
    p_malloc_1 = calloc(BSP_MALLOC_TEST_LENGTH, 1U);
    p_malloc = calloc(BSP_MALLOC_TEST_LENGTH, 1U);
    ASSERT(p_malloc_1 != NULL);
    ASSERT(p_malloc != NULL);

    for(i = 0U; i < BSP_MALLOC_TEST_LENGTH; i++)
    {
        ASSERT(p_malloc[i] == p_malloc_1[i]);
    }

    free(p_malloc);
    free(p_malloc_1);

    /* Test case 3: Malloc with size exceed the heap region */
    p_malloc = malloc(0x500);
    ASSERT(p_malloc == NULL);
}

#endif

void bsp_run_test(void)
{
    bsp_ioport_test_case();
#if (BSP_HEAP_SIZE > 0)
    bsp_heap_test_case();
#endif
}

#endif
