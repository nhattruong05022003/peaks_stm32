#include "main.h"

#if (RUN_BSP_TEST_CASE)

void abort(void)
{
    while(1);
}

void bsp_ioport_test_case(void)
{
    BSP_IO_Configurate(BSP_IO_PORTA_PIN_0, BSP_IO_CONFIG_OUTPUT_GPIO_PUSH_PULL | BSP_IO_MODE_OUTPUT_50MHZ);
    assert((GPIOA->CRL & 0x0F) == (BSP_IO_CONFIG_OUTPUT_GPIO_PUSH_PULL | BSP_IO_MODE_OUTPUT_50MHZ));
    BSP_IO_Write(BSP_IO_PORTA_PIN_0, BSP_IO_STATE_LOW);
    assert((GPIOA->ODR & 0x01) == BSP_IO_STATE_LOW);
    BSP_IO_Write(BSP_IO_PORTA_PIN_0, BSP_IO_STATE_HIGH);
    assert((GPIOA->ODR & 0x01) == BSP_IO_STATE_HIGH);
    BSP_IO_Toggle(BSP_IO_PORTA_PIN_0);
    assert((GPIOA->ODR & 0x01) == BSP_IO_STATE_LOW);
}
#if (BSP_HEAP_SIZE > 0)

void bsp_heap_test_case(void)
{
    uint8_t *p_malloc = malloc(4);
    assert(p_malloc != NULL);
    p_malloc[0] = 1;
    p_malloc[1] = 2;
    p_malloc[2] = 3;
    p_malloc[3] = 4;
    free(p_malloc);

    uint8_t *p_malloc_1 = malloc(4);
    p_malloc = malloc(4);
    assert(p_malloc_1 != NULL);
    assert(p_malloc != NULL);
    p_malloc[0] = 5;
    p_malloc[1] = 6;
    p_malloc[2] = 7;
    p_malloc[3] = 8;
    p_malloc_1[0] = 9;
    p_malloc_1[1] = 10;
    p_malloc_1[2] = 11;
    p_malloc_1[3] = 12;
    free(p_malloc);
    free(p_malloc_1);

    p_malloc = malloc(5);
    assert(p_malloc != NULL);
    p_malloc[0] = 1;
    p_malloc[1] = 2;
    p_malloc[2] = 3;
    p_malloc[3] = 4;
		p_malloc[4] = 5;
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