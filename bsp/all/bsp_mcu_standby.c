#include "bsp_mcu_standby.h"

/**********************************************************************************************************************
 * @brief Enable clock supply for all modules.
 *
 * @return None
 *********************************************************************************************************************/
void BSP_ModuleStandby_EnableAll(void)
{
    uint8_t module;
    volatile uint32_t *msr_reg;

    for(module = 0U; module < BSP_MODULE_STANDBY_TOTAL; module++)
    {
        msr_reg = g_bsp_module_standby_configs[module].msr_reg;
        *(msr_reg) |= (g_bsp_module_standby_configs[module].mask_value);
    }
}

/**********************************************************************************************************************
 * @brief Disable clock supply for all modules.
 *
 * @return None
 *********************************************************************************************************************/
void BSP_ModuleStandby_DisableAll(void)
{
    uint8_t module;
    volatile uint32_t *msr_reg;

    for(module = 0U; module < BSP_MODULE_STANDBY_TOTAL; module++)
    {
        msr_reg = g_bsp_module_standby_configs[module].msr_reg;
        *(msr_reg) &= ~(g_bsp_module_standby_configs[module].mask_value);
    }
}

/**********************************************************************************************************************
 * @brief Enable clock supply for specific module.
 *
 * @param module: Module need to be enabled clock.
 *
 * @return None
 *********************************************************************************************************************/
void BSP_ModuleStandby_EnableClock(bsp_module_standby_t module)
{
    volatile uint32_t *msr_reg = g_bsp_module_standby_configs[module].msr_reg;
    *(msr_reg) |= (g_bsp_module_standby_configs[module].mask_value);
}

/**********************************************************************************************************************
 * @brief Disable clock supply for specific module.
 *
 * @param module: Module need to be disabled clock.
 * 
 * @return None
 *********************************************************************************************************************/
void BSP_ModuleStandby_DisableClock(bsp_module_standby_t module)
{
    volatile uint32_t *msr_reg = g_bsp_module_standby_configs[module].msr_reg;
    *(msr_reg) &= ~(g_bsp_module_standby_configs[module].mask_value);
}
