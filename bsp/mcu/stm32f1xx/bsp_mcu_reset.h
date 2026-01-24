#ifndef _BSP_MCU_RESET_H_
#define _BSP_MCU_RESET_H_

#include "bsp_api.h"

/**
 * @brief Initialize state of output pin
 */
typedef enum e_bsp_low_power_mode
{
    BSP_LOW_POWER_MODE_LIGHT_SLEEP,
    BSP_LOW_POWER_MODE_DEEP_SLEEP,
    BSP_LOW_POWER_MODE_STANDBY
} bsp_low_power_mode_t;

/**********************************************************************************************************************
 * @brief Trigger MCU reset.
 *
 * @return None
 *********************************************************************************************************************/
__STATIC_ALWAYS_INLINE void BSP_McuReset_ResetTrigger(void)
{
    SCB->AIRCR_b.SYSRESETREQ = 1U;
}

/**********************************************************************************************************************
 * @brief Configurate PA0 as wake up pin.
 *
 * @return None
 *********************************************************************************************************************/
__STATIC_ALWAYS_INLINE void BSP_McuReset_ConfigWakeUpPin(void)
{
    PWR->CSR_b.EWUP = 1U; /* Config PA0 as wake up pin */
}

/**********************************************************************************************************************
 * @brief Config PA0 as GPIO.
 *
 * @return None
 *********************************************************************************************************************/
__STATIC_ALWAYS_INLINE void BSP_McuReset_DeconfigWakeUpPin(void)
{
    PWR->CSR_b.EWUP = 0U; /* Config PA0 as GPIO */
}

/**********************************************************************************************************************
 * @brief Clear wake-up flag.
 *
 * @return None
 *********************************************************************************************************************/
__STATIC_ALWAYS_INLINE void BSP_McuReset_WakeUpFlagClear(void)
{
    PWR->CR_b.CWUF = 1U;            /* Clear Wakeup Flag */
}

void BSP_McuReset_LowPowerModeTrigger(bsp_low_power_mode_t mode);

#endif
