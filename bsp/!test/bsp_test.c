#include "main.h"

#if (RUN_BSP_TEST_CASE)

void abort(void)
{
    while(1)
    {
        __asm__ volatile("nop");
    }
}

/**********************************************************************************************************************
 * @brief Test case testing IO Port.
 * Expect: Read / Write GPIO normally.
 *********************************************************************************************************************/
void bsp_ioport_test_case(void)
{
    BSP_IO_Configurate(BSP_IO_PORTA_PIN_2, BSP_IO_CONFIG_OUTPUT_GPIO_PUSH_PULL | BSP_IO_MODE_OUTPUT_50MHZ | BSP_IO_OUTPUT_INIT_STATE_HIGH);
    BSP_IO_Configurate(BSP_IO_PORTA_PIN_1, BSP_IO_CONFIG_INPUT_PULL_UP_DOWN | BSP_IO_INPUT_PULL_MODE_PULLHIGH);
    ASSERT(((GPIOA->CRL & (0x0FU << 8U)) >> 8U) == (BSP_IO_CONFIG_OUTPUT_GPIO_PUSH_PULL | BSP_IO_MODE_OUTPUT_50MHZ));
    BSP_IO_Write(BSP_IO_PORTA_PIN_2, BSP_IO_STATE_LOW);
    ASSERT(((GPIOA->ODR & 0x04U) >> 2U) == BSP_IO_STATE_LOW);
    ASSERT(BSP_IO_Read(BSP_IO_PORTA_PIN_1) == BSP_IO_STATE_LOW);
    BSP_IO_Write(BSP_IO_PORTA_PIN_2, BSP_IO_STATE_HIGH);
    ASSERT(((GPIOA->ODR & 0x04U) >> 2U) == BSP_IO_STATE_HIGH);
    ASSERT(BSP_IO_Read(BSP_IO_PORTA_PIN_1) == BSP_IO_STATE_HIGH);
    BSP_IO_Toggle(BSP_IO_PORTA_PIN_2);
    ASSERT(((GPIOA->ODR & 0x04U) >> 2U) == BSP_IO_STATE_LOW);
    ASSERT(BSP_IO_Read(BSP_IO_PORTA_PIN_1) == BSP_IO_STATE_LOW);
}

uint8_t bsp_irq_num = 0xFFU;

void WWDG_IRQHandler(void)
{
    bsp_irq_num = BSP_IRQ_GetIRQNumber();
}

void RTC_IRQHandler(void)
{
    bsp_irq_num = BSP_IRQ_GetIRQNumber();

    /* Trigger WDT IRQ */
    BSP_IRQ_SetPendingIRQ((IRQn_t) WWDG_IRQHandler_IRQ_Num);
    /* Immediately clear the pending WDT IRQ */
    BSP_IRQ_ClearPendingIRQ((IRQn_t) WWDG_IRQHandler_IRQ_Num);
}
/**********************************************************************************************************************
 * @brief Test case testing IRQ.
 * Expect: Functions related to IRQ can work normally.
 *********************************************************************************************************************/
void bsp_irq_test_case(void)
{
    volatile uint8_t timeout;
    /* Enable WDT IRQ */
    BSP_IRQ_Enable((IRQn_t) WWDG_IRQHandler_IRQ_Num);
    ASSERT((NVIC->ISER[0] & 0x01U) == (1U));

    /* Set priority 12 for WDT IRQ */
    BSP_IRQ_SetPriority((IRQn_t) WWDG_IRQHandler_IRQ_Num, 12U);
    ASSERT(BSP_IRQ_GetPriority((IRQn_t) WWDG_IRQHandler_IRQ_Num) == (12U));

    /* Trigger WDT IRQ */
    BSP_IRQ_SetPendingIRQ((IRQn_t) WWDG_IRQHandler_IRQ_Num);
    timeout = 0xFFU;
    while((timeout--) && (bsp_irq_num == 0xFFU));
    /* Verify the bsp_irq_num get the right number */
    ASSERT(timeout);
    ASSERT(bsp_irq_num == WWDG_IRQHandler_IRQ_Num);

    /* Enable RTC IRQ */
    BSP_IRQ_Enable((IRQn_t) RTC_IRQHandler_IRQ_Num);
    ASSERT((NVIC->ISER[0] & (0x01U << 3U)) == (1U << 3U));

    /* Set priority 11 for RTC IRQ */
    BSP_IRQ_SetPriority((IRQn_t) RTC_IRQHandler_IRQ_Num, 11U);
    ASSERT(BSP_IRQ_GetPriority((IRQn_t) RTC_IRQHandler_IRQ_Num) == (11U));

    bsp_irq_num = 0xFFU;
    BSP_IRQ_SetPendingIRQ((IRQn_t) RTC_IRQHandler_IRQ_Num);
    timeout = 0xFFU;
    while((timeout--) && (bsp_irq_num == 0xFFU));
    /* Verify the bsp_irq_num get the number of RTC not WDT since WDT IRQ has been cleared pending */
    ASSERT(timeout);
    ASSERT(bsp_irq_num == RTC_IRQHandler_IRQ_Num);

    BSP_IRQ_Disable((IRQn_t) WWDG_IRQHandler_IRQ_Num);
    ASSERT((NVIC->ISER[0] & 0x01U) == (0U));

    BSP_IRQ_Disable((IRQn_t) RTC_IRQHandler_IRQ_Num);
    ASSERT((NVIC->ISER[0] & (0x01U << 3U)) == 0U);
}

void PendSV_Handler(void)
{
    /* Trigger SVC exception */
    BSP_IRQ_SetPendingIRQ((IRQn_t) SVC_Handler_IRQ_Num);
    /* Immediately clear the pending SVC exception */
    BSP_IRQ_ClearPendingIRQ((IRQn_t) SVC_Handler_IRQ_Num);
}

uint8_t nmi_handler_execute = 0U;
void NMI_Handler(void)
{
    nmi_handler_execute = 1U;
}

/**********************************************************************************************************************
 * @brief Test case testing Exception.
 * Expect: Functions related to Exception can work normally.
 *********************************************************************************************************************/
void bsp_exception_test_case(void)
{
    /* Set priority 10 for SVC exception */
    BSP_IRQ_SetPriority((IRQn_t) SVC_Handler_IRQ_Num, 10U);
    ASSERT(BSP_IRQ_GetPriority((IRQn_t) SVC_Handler_IRQ_Num) == (10U));

    /* Set priority 9 for PendSV exception */
    BSP_IRQ_SetPriority((IRQn_t) PendSV_Handler_IRQ_Num, 9U);
    ASSERT(BSP_IRQ_GetPriority((IRQn_t) PendSV_Handler_IRQ_Num) == (9U));

    /* Trigger SVC exception */
    BSP_IRQ_SetPendingIRQ((IRQn_t) PendSV_Handler_IRQ_Num);

    nmi_handler_execute = 0U;
    /* Trigger NMI exception */
    BSP_IRQ_SetPendingNMIHandler();
    ASSERT(1U == nmi_handler_execute);
}

#if (BSP_HEAP_SIZE > 0)

#define BSP_MALLOC_TEST_LENGTH 128U

/**********************************************************************************************************************
 * @brief Test case testing heap region.
 * Expect: Using malloc, calloc to allocate the arrays in heap section normally.
 *********************************************************************************************************************/
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

    /* Test case 2: Calloc */
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

void bsp_mcu_reset_test_case(void)
{
    if(PWR->CSR_b.WUF != 1U)
    {
        BSP_McuReset_ConfigWakeUpPin();
        BSP_McuReset_LowPowerModeTrigger(BSP_LOW_POWER_MODE_STANDBY);
        while(1);
    }
    else
    {
        BSP_McuReset_WakeUpFlagClear();
        BSP_McuReset_DeconfigWakeUpPin();
    }
}

void bsp_run_test(void)
{
    bsp_mcu_reset_test_case();
    bsp_ioport_test_case();
    bsp_irq_test_case();
    bsp_exception_test_case();
#if (BSP_HEAP_SIZE > 0)
    bsp_heap_test_case();
#endif
}

#endif
