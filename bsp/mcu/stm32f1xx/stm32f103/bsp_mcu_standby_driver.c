#include "bsp_mcu_standby_driver.h"

const bsp_standby_config_t g_bsp_module_standby_configs[BSP_MODULE_STANDBY_TOTAL] = 
{
    [BSP_MODULE_STANDBY_ALTERNATIVE_FUNCTION_IO] = 
    {
        .msr_reg = (volatile uint32_t *) &(RCC->APB2ENR),
        .mask_value = 1U << 0
    },
    [BSP_MODULE_STANDBY_IO_PORT_A] = 
    {
        .msr_reg = (volatile uint32_t *) &(RCC->APB2ENR),
        .mask_value = 1U << 2
    },
    [BSP_MODULE_STANDBY_IO_PORT_B] = 
    {
        .msr_reg = (volatile uint32_t *) &(RCC->APB2ENR),
        .mask_value = 1U << 3
    },
    [BSP_MODULE_STANDBY_IO_PORT_C] = 
    {
        .msr_reg = (volatile uint32_t *) &(RCC->APB2ENR),
        .mask_value = 1U << 4
    },
    [BSP_MODULE_STANDBY_ADC_1] = 
    {
        .msr_reg = (volatile uint32_t *) &(RCC->APB2ENR),
        .mask_value = 1U << 9
    },
    [BSP_MODULE_STANDBY_ADC_2] = 
    {
        .msr_reg = (volatile uint32_t *) &(RCC->APB2ENR),
        .mask_value = 1U << 10
    },
    [BSP_MODULE_STANDBY_TIM_1] = 
    {
        .msr_reg = (volatile uint32_t *) &(RCC->APB2ENR),
        .mask_value = 1U << 11
    },
    [BSP_MODULE_STANDBY_SPI_1] = 
    {
        .msr_reg = (volatile uint32_t *) &(RCC->APB2ENR),
        .mask_value = 1U << 12
    },
    [BSP_MODULE_STANDBY_USART_1] = 
    {
        .msr_reg = (volatile uint32_t *) &(RCC->APB2ENR),
        .mask_value = 1U << 14
    },
    [BSP_MODULE_STANDBY_TIM_2] = 
    {
        .msr_reg = (volatile uint32_t *) &(RCC->APB1ENR),
        .mask_value = 1U << 0
    },
    [BSP_MODULE_STANDBY_TIM_3] = 
    {
        .msr_reg = (volatile uint32_t *) &(RCC->APB1ENR),
        .mask_value = 1U << 1
    },
    [BSP_MODULE_STANDBY_TIM_4] = 
    {
        .msr_reg = (volatile uint32_t *) &(RCC->APB1ENR),
        .mask_value = 1U << 2
    },
    [BSP_MODULE_STANDBY_TIM_5] = 
    {
        .msr_reg = (volatile uint32_t *) &(RCC->APB1ENR),
        .mask_value = 1U << 3
    },
    [BSP_MODULE_STANDBY_WDT] = 
    {
        .msr_reg = (volatile uint32_t *) &(RCC->APB1ENR),
        .mask_value = 1U << 11
    },
    [BSP_MODULE_STANDBY_SPI_2] = 
    {
        .msr_reg = (volatile uint32_t *) &(RCC->APB1ENR),
        .mask_value = 1U << 14
    },
    [BSP_MODULE_STANDBY_SPI_3] = 
    {
        .msr_reg = (volatile uint32_t *) &(RCC->APB1ENR),
        .mask_value = 1U << 15
    },
    [BSP_MODULE_STANDBY_USART_2] = 
    {
        .msr_reg = (volatile uint32_t *) &(RCC->APB1ENR),
        .mask_value = 1U << 17
    },
    [BSP_MODULE_STANDBY_USART_3] = 
    {
        .msr_reg = (volatile uint32_t *) &(RCC->APB1ENR),
        .mask_value = 1U << 18
    },
    [BSP_MODULE_STANDBY_USART_4] = 
    {
        .msr_reg = (volatile uint32_t *) &(RCC->APB1ENR),
        .mask_value = 1U << 19
    },
    [BSP_MODULE_STANDBY_USART_5] = 
    {
        .msr_reg = (volatile uint32_t *) &(RCC->APB1ENR),
        .mask_value = 1U << 20
    },
    [BSP_MODULE_STANDBY_I2C_1] = 
    {
        .msr_reg = (volatile uint32_t *) &(RCC->APB1ENR),
        .mask_value = 1U << 21
    },
    [BSP_MODULE_STANDBY_I2C_2] = 
    {
        .msr_reg = (volatile uint32_t *) &(RCC->APB1ENR),
        .mask_value = 1U << 22
    },
    [BSP_MODULE_STANDBY_CAN_1] = 
    {
        .msr_reg = (volatile uint32_t *) &(RCC->APB1ENR),
        .mask_value = 1U << 25
    },
    [BSP_MODULE_STANDBY_CAN_2] = 
    {
        .msr_reg = (volatile uint32_t *) &(RCC->APB1ENR),
        .mask_value = 1U << 26
    },
    [BSP_MODULE_STANDBY_BACKUP_INTERFACE] = 
    {
        .msr_reg = (volatile uint32_t *) &(RCC->APB1ENR),
        .mask_value = 1U << 27
    },
    [BSP_MODULE_STANDBY_POWER_INTERFACE] = 
    {
        .msr_reg = (volatile uint32_t *) &(RCC->APB1ENR),
        .mask_value = 1U << 28
    },
    [BSP_MODULE_STANDBY_DMAC_1] = 
    {
        .msr_reg = (volatile uint32_t *) &(RCC->AHBENR),
        .mask_value = 1U << 0
    },
    [BSP_MODULE_STANDBY_DMAC_2] = 
    {
        .msr_reg = (volatile uint32_t *) &(RCC->AHBENR),
        .mask_value = 1U << 1
    },
    [BSP_MODULE_STANDBY_SRAM] = 
    {
        .msr_reg = (volatile uint32_t *) &(RCC->AHBENR),
        .mask_value = 1U << 2
    },
    [BSP_MODULE_STANDBY_FLITF] = 
    {
        .msr_reg = (volatile uint32_t *) &(RCC->AHBENR),
        .mask_value = 1U << 4
    },
    [BSP_MODULE_STANDBY_CRC] = 
    {
        .msr_reg = (volatile uint32_t *) &(RCC->AHBENR),
        .mask_value = 1U << 6
    }
};