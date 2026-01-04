#ifndef _BSP_IRQ_H_
#define _BSP_IRQ_H_

#include "bsp_api.h"
#include "bsp_irq_driver.h"

/**********************************************************************************************************************
 * @brief Enable specific interrupt.
 *
 * @param IRQn: The IRQ channel number to be enabled.
 *
 * @return None
 *********************************************************************************************************************/
__STATIC_INLINE void BSP_IRQ_Enable(IRQn_t IRQn)
{
    NVIC->ISER[IRQn / 32U] |= (1U << (IRQn % 32U));
}

/**********************************************************************************************************************
 * @brief Disable specific interrupt.
 *
 * @param IRQn: The IRQ channel number to be disabled.
 *
 * @return None
 *********************************************************************************************************************/
__STATIC_INLINE void BSP_IRQ_Disable(IRQn_t IRQn)
{
    NVIC->ICER[IRQn / 32U] |= (1U << (IRQn % 32U));
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
    NVIC->IPR[IRQn] = ((uint8_t)(priority & 0x0FU)) << 4U;
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
    return (uint8_t) (NVIC->IPR[IRQn] >> 4U);
}

/**********************************************************************************************************************
 * @brief Set IRQn pending.
 *
 * @param IRQn: The IRQ channel number to be set to pending state.
 *
 * @return None
 *********************************************************************************************************************/
__STATIC_INLINE void BSP_IRQ_SetPendingIRQ (IRQn_t IRQn)
{
    NVIC->ISPR[IRQn / 32U] |= (1U << (IRQn % 32U));
}

/**********************************************************************************************************************
 * @brief Clear IRQn pending.
 *
 * @param IRQn: The IRQ channel number to be cleared the pending state.
 *
 * @return None
 *********************************************************************************************************************/
__STATIC_INLINE void BSP_IRQ_ClearPendingIRQ (IRQn_t IRQn)
{
    NVIC->ICPR[IRQn / 32U] |= (1U << (IRQn % 32U));
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
