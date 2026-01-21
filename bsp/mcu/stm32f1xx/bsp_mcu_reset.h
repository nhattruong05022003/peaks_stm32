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

void BSP_McuReset_LowPowerModeTrigger(bsp_low_power_mode_t mode);

#endif
