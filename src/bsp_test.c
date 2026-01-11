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

void bsp_run_test(void)
{
    bsp_ioport_test_case();
}

#endif