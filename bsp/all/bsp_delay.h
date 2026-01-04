#ifndef _BSP_DELAY_H_
#define _BSP_DELAY_H_

#include "bsp_common.h"

/**
 * @brief Time units for delay functions.
 */
typedef enum e_bsp_delay_unit
{
    BSP_DELAY_UNIT_MICROSECOND = 1000000,
    BSP_DELAY_UNIT_MILLISECOND = 1000,
    BSP_DELAY_UNIT_SECOND = 1
} bsp_delay_unit_t;

void BSP_Software_Delay(bsp_delay_unit_t unit, uint32_t time);

#endif
