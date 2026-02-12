#ifndef _DMA_H_
#define _DMA_H_

#include "bsp_api.h"

#define DMA_TRANFER_IRQ_FLAG(channel) (1U << ((channel * 4U) + 1U))
#define DMA_HALF_TRANFER_IRQ_FLAG(channel) (1U << ((channel * 4U) + 2U))
#define DMA_TRANFER_ERROR_IRQ_FLAG(channel) (1U << ((channel * 4U) + 3U))

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
