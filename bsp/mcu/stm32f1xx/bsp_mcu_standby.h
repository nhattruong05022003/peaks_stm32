#ifndef _BSP_MCU_STANDBY_H_
#define _BSP_MCU_STANDBY_H_

#include "bsp_mcu_standby_driver.h"

#define BSP_MODULE_STANDBY_REG_TYPE_MASK (0xFFU << 8)
#define BSP_MODULE_STANDBY_REG_BIT_MASK (0xFFU)

void BSP_ModuleStandby_EnableAll(void);
void BSP_ModuleStandby_DisableAll(void);
void BSP_ModuleStandby_EnableClock(bsp_module_standby_t module);
void BSP_ModuleStandby_DisableClock(bsp_module_standby_t module);

#endif
