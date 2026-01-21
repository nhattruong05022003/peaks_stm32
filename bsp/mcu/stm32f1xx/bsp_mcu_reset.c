#include "bsp_mcu_reset.h"

static void bsp_light_sleep_mode_trigger(void);
static void bsp_deep_sleep_mode_trigger(void);
static void bsp_standby_mode_trigger(void);

/* Array that contains function pointer for low power mode */
void (*const g_bsp_mcu_reset_funcs[])(void) =
{
    bsp_light_sleep_mode_trigger,
    bsp_deep_sleep_mode_trigger,
    bsp_standby_mode_trigger
};

/**********************************************************************************************************************
 * @brief Enter a specific low power mode.
 *
 * @param mode: Low power mode that MCU will enter.
 * 
 * @return None
 *********************************************************************************************************************/
void BSP_McuReset_LowPowerModeTrigger(bsp_low_power_mode_t mode)
{
    g_bsp_mcu_reset_funcs[(uint8_t) mode]();
}

/**********************************************************************************************************************
 * @brief Enter light sleep mode.
 *
 * @return None
 *********************************************************************************************************************/
static void bsp_light_sleep_mode_trigger(void)
{
    SCB->SCR_b.SLEEPDEEP = 0U; /* Mode normal sleep */
    __WFI();                   /* Wait For Interrupt */ 
}

/**********************************************************************************************************************
 * @brief Enter deep sleep mode.
 *
 * @return None
 *********************************************************************************************************************/
static void bsp_deep_sleep_mode_trigger(void)
{
    RCC->APB1ENR_b.PWREN = 1U;      /* Ensure Power Clock has been enabled */
    SCB->SCR_b.SLEEPDEEP = 1U;      /* Enable Cortex-M3 Deep Sleep */
    PWR->CR_b.PDDS = 0U;            /* PDDS = 0 (Stop Mode) */
    PWR->CR_b.LPDS = 1U;            /* Voltage regulator in low-power mode during Stop mode */
    __WFI();                        /* Wait For Interrupt */ 
}

/**********************************************************************************************************************
 * @brief Enter standby sleep mode.
 *
 * @return None
 *********************************************************************************************************************/
static void bsp_standby_mode_trigger(void)
{
    RCC->APB1ENR_b.PWREN = 1U;      /* Ensure Power Clock has been enabled */
    SCB->SCR_b.SLEEPDEEP = 1U;      /* Enable Cortex-M3 Deep Sleep */
    PWR->CR_b.PDDS = 1U;            /* PDDS = 1 (Standby mode) */
    PWR->CR_b.CWUF = 1U;            /* Clear Wakeup Flag */
    __WFI();                        /* Wait For Interrupt */ 
}
