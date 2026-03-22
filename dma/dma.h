#ifndef _DMA_H_
#define _DMA_H_

#include "bsp_api.h"

#define DMA_TRANFER_IRQ_FLAG(channel) (1U << ((channel * 4U) + 1U))
#define DMA_HALF_TRANFER_IRQ_FLAG(channel) (1U << ((channel * 4U) + 2U))
#define DMA_TRANFER_ERROR_IRQ_FLAG(channel) (1U << ((channel * 4U) + 3U))

/**
 * @brief  Summary of DMA1 Request Mapping
 * | Peripherals | Ch 1    | Ch 2      | Ch 3      | Ch 4      | Ch 5      | Ch 6      | Ch 7      |
 * |-------------|---------|-----------|-----------|-----------|-----------|-----------|-----------|
 * | ADC1        | ADC1    | -         | -         | -         | -         | -         | -         |
 * | SPI/I2S     | -       | SPI1_RX   | SPI1_TX   | SPI2_RX   | SPI2_TX   | -         | -         |
 * | USART       | -       | USART3_TX | USART3_RX | USART1_TX | USART1_RX | USART2_RX | USART2_TX |
 * | I2C         | -       | -         | -         | I2C2_TX   | I2C2_RX   | I2C1_TX   | I2C1_RX   |
 * | TIM1        | -       | TIM1_CH1  | -         | TIM1_CH4  | TIM1_UP   | -         | -         |
 * |             |         |           |           | TIM1_TRIG | TIM1_CH3  |           |           |
 * |             |         |           |           | TIM1_COM  |           |           |           |
 * | TIM2        | TIM2_CH3| TIM2_UP   | -         | -         | TIM2_CH1  | -         | TIM2_CH2  |
 * |             |         |           |           |           | TIM2_CH4  |           |           |
 * | TIM3        | -       | TIM3_CH3  | TIM3_CH4  | -         | -         | TIM3_CH1  | -         |
 * |             |         |           | TIM3_UP   |           |           | TIM3_TRIG |           |
 * | TIM4        | TIM4_CH1| -         | -         | TIM4_CH2  | TIM4_CH3  | -         | TIM4_UP   |
 *
 * @note Memory-to-Memory (M2M) mode is supported on all channels.
 */

/**
 * @brief DMA2 controller
 * The five requests from the peripherals (TIMx[5,6,7,8], ADC3, SPI/I2S3, UART4,
 * DAC_Channel[1,2] and SDIO) are simply logically ORed before entering the DMA2, this
 * means that only one request must be enabled at a time.
 */

/**
 * @brief DMA Unit
 */
typedef enum e_dma_unit
{
    DMA_UNIT_1,
    DMA_UNIT_2
} dma_unit_t;

/**
 * @brief DMA tranfer direction
 */
typedef enum e_dma_tranfer_direction
{
    DMA_TRANFER_DIRECTION_READ_FROM_PERIPH,
    DMA_TRANFER_DIRECTION_READ_FROM_MEM
} dma_tranfer_direction_t;

/**
 * @brief DMA circular mode
 */
typedef enum e_dma_circular_mode
{
    DMA_CIRCULAR_MODE_DISABLE,
    DMA_CIRCULAR_MODE_ENABLE
} dma_circular_mode_t;

/**
 * @brief DMA peripheral increment mode
 */
typedef enum e_dma_periph_inc_mode
{
    DMA_PERIPH_INC_MODE_DISABLE,
    DMA_PERIPH_INC_MODE_ENABLE
} dma_periph_inc_mode_t;

/**
 * @brief DMA memory increment mode
 */
typedef enum e_dma_mem_inc_mode
{
    DMA_MEM_INC_MODE_DISABLE,
    DMA_MEM_INC_MODE_ENABLE
} dma_mem_inc_mode_t;

/**
 * @brief DMA memory to memory mode
 */
typedef enum e_dma_mem2mem_mode
{
    DMA_MEM2MEM_MODE_DISABLE,
    DMA_MEM2MEM_MODE_ENABLE
} dma_mem2mem_mode_t;

/**
 * @brief DMA peripheral size
 */
typedef enum e_dma_periph_size
{
    DMA_PERIPH_SIZE_8_BITS,
    DMA_PERIPH_SIZE_16_BITS,
    DMA_PERIPH_SIZE_32_BITS
} dma_periph_size_t;

/**
 * @brief DMA memory size
 */
typedef enum e_dma_mem_size
{
    DMA_MEM_SIZE_8_BITS,
    DMA_MEM_SIZE_16_BITS,
    DMA_MEM_SIZE_32_BITS
} dma_mem_size_t;

/**
 * @brief DMA channel priority
 */
typedef enum e_dma_channel_priority
{
    DMA_CHANNEL_PRIORITY_LOW,
    DMA_CHANNEL_PRIORITY_MEDIUM,
    DMA_CHANNEL_PRIORITY_HIGH,
    DMA_CHANNEL_PRIORITY_VERYHIGH
} dma_channel_priority_t;

/**
 * @brief DMA configuration
 */
typedef struct st_dma_cfg
{
    union
    {
        uint16_t configuration;
        struct
        {
            uint16_t tranfer_direction : 1; ///< Tranfer direction
            uint16_t circular_mode : 1; ///< Circular mode
            uint16_t periph_inc_mode : 1; ///< Peripheral increment mode
            uint16_t mem_inc_mode : 1; ///< Memory increment mode
            uint16_t m2m_mode : 1; ///< Memory to memory mode
            uint16_t periph_size : 2; ///< Peripheral size
            uint16_t mem_size : 2; ///< Memory size
            uint16_t channel_priority : 2; ///< Channel priority level
        } configuration_b;
    };
    uint8_t tranfer_ipl; ///< Tranfer interrupt priority
    uint8_t half_tranfer_ipl; ///< Half-tranfer interrupt priority
    uint8_t err_ipl; ///< Error interrupt priority
    uint8_t channel; ///< DMA channel
    dma_unit_t unit; ///< DMA Unit
} dma_cfg_t;

extern DMAx_Type * dma_unit_list[];

/**
 * @brief DMA control structure. This struct will be set up by function.
 * Do not manually change the value of this struct.
 */
typedef struct st_dma_ctrl
{
    const dma_cfg_t *p_cfg; ///< Pointer to configuration struct
    DMAx_Type *p_reg; ///< Pointer to DMA register
    void (*p_callback)(void *p_args); ///< Poiter to user callback function
    uint32_t open; ///< Open status
} dma_ctrl_t;

void DMA_Open(dma_ctrl_t *p_ctrl, const dma_cfg_t *p_cfg);
void DMA_Start(dma_ctrl_t *p_ctrl, const uint32_t src, const uint32_t dest, uint16_t size);
void DMA_Stop(dma_ctrl_t *p_ctrl);
void DMA_Close(dma_ctrl_t *p_ctrl);

#endif
