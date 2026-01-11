#include "bsp_io.h"

#define BSP_IO_BYTE_MASK (0xFFU)

/* GPIO port array */
static GPIOx_Type * bsp_port_list[] = 
{
    GPIOA,
    GPIOB,
    GPIOC
};

/**********************************************************************************************************************
 * @brief Configurate a specific GPIO pin with input config.
 *
 * @param pin: Specific GPIO pin to be configurated.
 * @param config: Specific configuration for the GPIO pin.
 *
 * @return None
 *********************************************************************************************************************/
void BSP_IO_Configurate(bsp_io_t pin, uint8_t config)
{
    uint8_t config_pin = pin & BSP_IO_BYTE_MASK;
    uint8_t config_port = (pin & (BSP_IO_BYTE_MASK << BSP_IO_PORT_TYPE_SHIFT)) >> BSP_IO_PORT_TYPE_SHIFT;

    if(config_pin >= 8U)
    {
        /* Clear config pin */
        bsp_port_list[config_port]->CRH &= ~(0x0FU << ((config_pin - 8U) * 4U));

        /* Config pin */
        bsp_port_list[config_port]->CRH |= (config << ((config_pin - 8U)* 4U));
    }
    else
    {
        /* Clear config pin */
        bsp_port_list[config_port]->CRL &= ~(0x0FU << (config_pin * 4U));

        /* Config pin */
        bsp_port_list[config_port]->CRL |= (config << (config_pin * 4U));
    }
}

/**********************************************************************************************************************
 * @brief Change state for a specific GPIO pin.
 *
 * @param pin: GPIO pin that need to be changed state.
 * @param config: State for this GPIO pin.
 *
 * @return None
 *********************************************************************************************************************/
void BSP_IO_Write(bsp_io_t pin, bsp_io_state_t state)
{
    uint8_t config_pin = pin & BSP_IO_BYTE_MASK;
    uint8_t config_port = (pin & (BSP_IO_BYTE_MASK << BSP_IO_PORT_TYPE_SHIFT)) >> BSP_IO_PORT_TYPE_SHIFT;

    if(BSP_IO_STATE_LOW == state)
    {
        bsp_port_list[config_port]->ODR &= ~(1U << config_pin);
    }
    else
    {
        bsp_port_list[config_port]->ODR |= (1U << config_pin);
    }
}

/**********************************************************************************************************************
 * @brief Toggle state for a specific GPIO pin.
 *
 * @param pin: GPIO pin that state need to be toggled.
 *
 * @return None
 *********************************************************************************************************************/
void BSP_IO_Toggle(bsp_io_t pin)
{
    uint8_t config_pin = pin & BSP_IO_BYTE_MASK;
    uint8_t config_port = (pin & (BSP_IO_BYTE_MASK << BSP_IO_PORT_TYPE_SHIFT)) >> BSP_IO_PORT_TYPE_SHIFT;

    bsp_port_list[config_port]->ODR ^= (1U << config_pin);
}

/**********************************************************************************************************************
 * @brief Return the state of specific pin.
 *
 * @param pin: GPIO pin that need to be read state.
 *
 * @return None
 *********************************************************************************************************************/
bsp_io_state_t BSP_IO_Read(bsp_io_t pin)
{
    bsp_io_state_t state;
    uint8_t config_pin = pin & BSP_IO_BYTE_MASK;
    uint8_t config_port = (pin & (BSP_IO_BYTE_MASK << BSP_IO_PORT_TYPE_SHIFT)) >> BSP_IO_PORT_TYPE_SHIFT;
    state = (bsp_port_list[config_port]->IDR & (1U << config_pin)) >> config_pin;
    return state;
}
