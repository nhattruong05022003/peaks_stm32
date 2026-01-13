#ifndef _BSP_IRQ_H_
#define _BSP_IRQ_H_

#include "bsp_api.h"
#include "bsp_irq_driver.h"

extern uint8_t* bsp_exception_priority_regs[];

/**********************************************************************************************************************
 * @brief Enable specific interrupt. Only for interrupt events, not including exception.
 *
 * @param IRQn: The IRQ channel number to be enabled. (Must be greater than or equal 0)
 *
 * @return None
 *********************************************************************************************************************/
__STATIC_INLINE void BSP_IRQ_Enable(IRQn_t IRQn)
{
    if(IRQn >= (IRQn_t) 0)
    {
        NVIC->ISER[IRQn / 32U] |= (1U << (IRQn % 32U));
    }
}

/**********************************************************************************************************************
 * @brief Disable specific interrupt. Only for interrupt events, not including exception.
 *
 * @param IRQn: The IRQ channel number to be disabled. (Must be greater than or equal 0)
 *
 * @return None
 *********************************************************************************************************************/
__STATIC_INLINE void BSP_IRQ_Disable(IRQn_t IRQn)
{
    if(IRQn >= (IRQn_t) 0)
    {
        NVIC->ICER[IRQn / 32U] |= (1U << (IRQn % 32U));
    }
}

/**********************************************************************************************************************
 * @brief Set priority for the specific interrupt.
 *
 * @param IRQn: The IRQ channel number.
 * @param priority: Priority
 *
 * @return None
 *********************************************************************************************************************/
__STATIC_INLINE void BSP_IRQ_SetPriority (IRQn_t IRQn, uint32_t priority)
{
    if(IRQn < (IRQn_t) 0)
    {
        *bsp_exception_priority_regs[(IRQn + BSP_EXCEPTION_OFFSET)] = ((uint8_t)(priority & 0x0FU)) << 4U;
    }
    else
    {
        NVIC->IPR[IRQn] = ((uint8_t)(priority & 0x0FU)) << 4U;
    }
}

/**********************************************************************************************************************
 * @brief Get priority of the specific interrupt.
 *
 * @param IRQn: The IRQ channel number.
 *
 * @return Priority of the interrupt.
 *********************************************************************************************************************/
__STATIC_INLINE uint8_t BSP_IRQ_GetPriority (IRQn_t IRQn)
{
    uint8_t priority_value;
    if(IRQn < (IRQn_t) 0)
    {
        priority_value = *bsp_exception_priority_regs[(IRQn + BSP_EXCEPTION_OFFSET)];
    }
    else
    {
        priority_value = NVIC->IPR[IRQn];
    }
    return (uint8_t) (priority_value >> 4U);
}

/**********************************************************************************************************************
 * @brief Set IRQn pending. Only for interrupt events, SysTick and PendSV exception.
 *
 * @param IRQn: The IRQ channel number to be set to pending state.
 *
 * @return None
 *********************************************************************************************************************/
__STATIC_INLINE void BSP_IRQ_SetPendingIRQ (IRQn_t IRQn)
{
    if(IRQn == PendSV_Handler_IRQ_Num)
    {
        SCB->ICSR_b.PENDSVSET = 1U;
    }
    else if (IRQn == SysTick_Handler_IRQ_Num)
    {
        SCB->ICSR_b.PENDSTSET = 1U;
    }
    else if(IRQn >= (IRQn_t) 0)
    {
        NVIC->ISPR[IRQn / 32U] |= (1U << (IRQn % 32U));
    }
    else
    {
        /* Do nothing */
    }
}

/**********************************************************************************************************************
 * @brief Clear IRQn pending. Only for interrupt events, SysTick and PendSV exception.
 *
 * @param IRQn: The IRQ channel number to be cleared the pending state.
 *
 * @return None
 *********************************************************************************************************************/
__STATIC_INLINE void BSP_IRQ_ClearPendingIRQ (IRQn_t IRQn)
{
    if(IRQn == PendSV_Handler_IRQ_Num)
    {
        SCB->ICSR_b.PENDSVCLR = 1U;
    }
    else if (IRQn == SysTick_Handler_IRQ_Num)
    {
        SCB->ICSR_b.PENDSTCLR = 1U;
    }
    else if(IRQn >= (IRQn_t) 0)
    {
        NVIC->ICPR[IRQn / 32U] |= (1U << (IRQn % 32U));
    }
    else
    {
        /* Do nothing */
    }
}

/**********************************************************************************************************************
 * @brief Get IRQ number of the current active interrupt.
 *
 * @return None
 *********************************************************************************************************************/
__STATIC_INLINE IRQn_t BSP_IRQ_GetIRQNumber (void)
{
    IRQn_t irq_num = (IRQn_t)((__get_xPSR() & 0xFFU) - 16u);
    return irq_num;
}

#endif
