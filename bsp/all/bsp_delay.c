#include "bsp_delay.h"

/* Variable storing System Clock */
uint32_t SystemClockHz;

/**********************************************************************************************************************
 * @brief Delay a specific of time.
 *
 * @param unit: The time unit to be used (e.g., microseconds, milliseconds, seconds).
 * @param time: The amount of time to delay.
 *
 * @return None
 *********************************************************************************************************************/
void BSP_Software_Delay(bsp_delay_unit_t unit, uint32_t time)
{
    uint32_t load_val;
    volatile uint32_t loop = time;

    SysTick->STK_CTRL_b.TICKINT = 0U; /* No interrupt */
    SysTick->STK_CTRL_b.CLKSOURCE = 1U; /* Clock source = AHB = 72MHz */
    load_val = SystemClockHz / (((uint32_t) unit)); /* Calculate value needed for 1 unit (us, ms, s) */
    SysTick->STK_LOAD_b.RELOAD = load_val; /* Set load value */
    SysTick->STK_CTRL_b.ENABLE = 1U; /* Enable Systick */

    while(loop --)
    {   
        while (0U == SysTick->STK_CTRL_b.COUNTFLAG); /* Wait for flag = 1 */
    }
    
    SysTick->STK_CTRL_b.ENABLE = 0U; /* Disable Systick */
}