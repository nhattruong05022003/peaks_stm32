#ifndef _BSP_IO_H_
#define _BSP_IO_H_

#include "bsp_io_driver.h"

#define BSP_IO_MODE_SHIFT (8U)
#define BSP_IO_CONFIG_SHIFT (16U)

/**
 * @brief IO Port configuration
 */
typedef enum e_bsp_io_config
{
    BSP_IO_CONFIG_INPUT_ANALOG = (0U << 2U),
    BSP_IO_CONFIG_INPUT_FLOATING = (1U << 2U),
    BSP_IO_CONFIG_INPUT_PULL_UP_DOWN = (2U << 2U),

    BSP_IO_CONFIG_OUTPUT_GPIO_PUSH_PULL = (0U << 2U),
    BSP_IO_CONFIG_OUTPUT_GPIO_OPEN_DRAIN = (1U << 2U),
    BSP_IO_CONFIG_OUTPUT_ALTER_PUSH_PULL = (2U << 2U),
    BSP_IO_CONFIG_OUTPUT_ALTER_OPEN_DRAIN = (3U << 2U)
} bsp_io_config_t;

/**
 * @brief IO Port mode
 */
typedef enum e_bsp_io_mode
{
    BSP_IO_MODE_INPUT = 0U,
    BSP_IO_MODE_OUTPUT_10MHZ = 1U,
    BSP_IO_MODE_OUTPUT_2MHZ = 2U,
    BSP_IO_MODE_OUTPUT_50MHZ = 3U
} bsp_io_mode_t;

/**
 * @brief IO Port state
 */
typedef enum e_bsp_io_state
{
    BSP_IO_STATE_LOW = 0U,
    BSP_IO_STATE_HIGH = 1U
} bsp_io_state_t;

void BSP_IO_Configurate(bsp_io_t pin, uint8_t config);
void BSP_IO_Write(bsp_io_t pin, bsp_io_state_t state);
void BSP_IO_Toggle(bsp_io_t pin);
bsp_io_state_t BSP_IO_Read(bsp_io_t pin);

#endif