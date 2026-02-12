#include "main.h"

#if (RUN_DMA_TEST_CASE)

#define TEST_SIZE 2048

uint8_t src[TEST_SIZE];
uint8_t dest[TEST_SIZE];

uint8_t src1[TEST_SIZE];
uint8_t dest1[TEST_SIZE];

dma_ctrl_t dma_ctrl1;
dma_cfg_t dma_cfg1 = 
{
    .configuration_b = 
    {
        .tranfer_direction = DMA_TRANFER_DIRECTION_READ_FROM_PERIPH,
        .circular_mode = DMA_CIRCULAR_MODE_DISABLE,
        .m2m_mode = DMA_MEM2MEM_MODE_ENABLE,
        .mem_inc_mode = DMA_MEM_INC_MODE_ENABLE,
        .periph_inc_mode = DMA_PERIPH_INC_MODE_ENABLE,
        .mem_size = DMA_MEM_SIZE_8_BITS,
        .periph_size = DMA_PERIPH_SIZE_8_BITS,
        .channel_priority = DMA_CHANNEL_PRIORITY_MEDIUM
    },
    .tranfer_ipl = BSP_IRQ_DISABLE,
    .half_tranfer_ipl = BSP_IRQ_DISABLE,
    .err_ipl = BSP_IRQ_DISABLE,
    .channel = 1U,
    .unit = DMA_UNIT_1
};

dma_ctrl_t dma_ctrl2;
dma_cfg_t dma_cfg2 = 
{
    .configuration_b = 
    {
        .tranfer_direction = DMA_TRANFER_DIRECTION_READ_FROM_PERIPH,
        .circular_mode = DMA_CIRCULAR_MODE_DISABLE,
        .m2m_mode = DMA_MEM2MEM_MODE_ENABLE,
        .mem_inc_mode = DMA_MEM_INC_MODE_ENABLE,
        .periph_inc_mode = DMA_PERIPH_INC_MODE_ENABLE,
        .mem_size = DMA_MEM_SIZE_8_BITS,
        .periph_size = DMA_PERIPH_SIZE_8_BITS,
        .channel_priority = DMA_CHANNEL_PRIORITY_MEDIUM
    },
    .tranfer_ipl = BSP_IRQ_DISABLE,
    .half_tranfer_ipl = BSP_IRQ_DISABLE,
    .err_ipl = BSP_IRQ_DISABLE,
    .channel = 4U,
    .unit = DMA_UNIT_1
};

static volatile uint8_t tranfer_irq_flag = 0U;
static volatile uint8_t half_tranfer_irq_flag = 0U;
static volatile uint8_t tranfer_error_irq_flag = 0U;
void DMA_user_callback(void *p_args)
{
    dma_ctrl_t *p_ctrl = (dma_ctrl_t *)p_args;
    uint8_t channel = p_ctrl->p_cfg->channel - 1U;

    if((p_ctrl->p_reg->ISR & DMA_TRANFER_IRQ_FLAG(channel)) && \
        (p_ctrl->p_reg->DMA_Channelx_Reg[channel].CCRx_b.TCIE))
    {
        tranfer_irq_flag ++;
    }

    if((p_ctrl->p_reg->ISR & DMA_HALF_TRANFER_IRQ_FLAG(channel)) && \
        (p_ctrl->p_reg->DMA_Channelx_Reg[channel].CCRx_b.HTIE))
    {
        half_tranfer_irq_flag ++;
    }

    if((p_ctrl->p_reg->ISR & DMA_TRANFER_ERROR_IRQ_FLAG(channel)) && \
        (p_ctrl->p_reg->DMA_Channelx_Reg[channel].CCRx_b.TEIE))
    {
        tranfer_error_irq_flag ++;
    }
}

static volatile uint8_t tranfer_irq_flag1 = 0U;
static volatile uint8_t half_tranfer_irq_flag1 = 0U;
void DMA_user_callback_1(void *p_args)
{
    dma_ctrl_t *p_ctrl = (dma_ctrl_t *)p_args;
    uint8_t channel = p_ctrl->p_cfg->channel - 1U;

    if((p_ctrl->p_reg->ISR & DMA_TRANFER_IRQ_FLAG(channel)) && \
        (p_ctrl->p_reg->DMA_Channelx_Reg[channel].CCRx_b.TCIE))
    {
        tranfer_irq_flag1 ++;
    }

    if((p_ctrl->p_reg->ISR & DMA_HALF_TRANFER_IRQ_FLAG(channel)) && \
        (p_ctrl->p_reg->DMA_Channelx_Reg[channel].CCRx_b.HTIE))
    {
        half_tranfer_irq_flag1 ++;
    }
}

void dma_mem_2_mem_test_case(void)
{
    uint16_t i;

    /* Test case 1 */
    for(i = 0U; i < TEST_SIZE; i++)
    {
        src[i] = 'A' + (i % 26U);
    }

    for(i = 0U; i < TEST_SIZE; i++)
    {
        dest[i] = 0U;
    }

    DMA_Open(&dma_ctrl1, &dma_cfg1);
    DMA_Start(&dma_ctrl1, (uint32_t)&src, (uint32_t)&dest, TEST_SIZE);
    
    BSP_Software_Delay(BSP_DELAY_UNIT_MILLISECOND, 1U);

    /* Clear interrupt flag */
    dma_ctrl1.p_reg->IFCR |= 1U;
    DMA_Stop(&dma_ctrl1);
	
    /* Verify the tranfer */
    for(i = 0U; i < TEST_SIZE; i++)
    {
        ASSERT(src[i] == dest[i]);
    }

    /* Test case 2 */
    for(i = 0U; i < TEST_SIZE; i++)
    {
        src[i] = 'a' + (i % 26U);
    }

    for(i = 0U; i < TEST_SIZE; i++)
    {
        dest[i] = 0U;
    }

    DMA_Start(&dma_ctrl1, (uint32_t)&src, (uint32_t)&dest, TEST_SIZE);
    
    BSP_Software_Delay(BSP_DELAY_UNIT_MILLISECOND, 1U);

    /* Clear interrupt flag */
    dma_ctrl1.p_reg->IFCR |= 1U;
    DMA_Stop(&dma_ctrl1);

    /* Verify the tranfer */
    for(i = 0U; i < TEST_SIZE; i++)
    {
        ASSERT(src[i] == dest[i]);
    }
		
    DMA_Close(&dma_ctrl1);

    /* Test case 3 */
    for(i = 0U; i < TEST_SIZE; i++)
    {
        src[i] = 'A' + (i % 26U);
    }

    for(i = 0U; i < TEST_SIZE; i++)
    {
        dest[i] = 0U;
    }

    dma_cfg1.configuration_b.periph_size = DMA_PERIPH_SIZE_32_BITS;
    dma_cfg1.configuration_b.mem_size = DMA_MEM_SIZE_32_BITS;
    DMA_Open(&dma_ctrl1, &dma_cfg1);
    DMA_Start(&dma_ctrl1, (uint32_t)&src, (uint32_t)&dest, TEST_SIZE / 4U);
    
    BSP_Software_Delay(BSP_DELAY_UNIT_MILLISECOND, 1U);

    /* Clear interrupt flag */
    dma_ctrl1.p_reg->IFCR |= 1U;
    DMA_Stop(&dma_ctrl1);

    /* Verify the tranfer */
    for(i = 0U; i < TEST_SIZE; i++)
    {
        ASSERT(src[i] == dest[i]);
    }
		
    DMA_Close(&dma_ctrl1);
}

void dma_mem_2_mem_interrupt_test_case(void)
{
    uint16_t i;

    /* Test case 1 */
    tranfer_irq_flag = 0U;
    half_tranfer_irq_flag = 0U;
    dma_cfg1.configuration_b.periph_size = DMA_PERIPH_SIZE_8_BITS;
    dma_cfg1.configuration_b.mem_size = DMA_MEM_SIZE_8_BITS;
    dma_cfg1.tranfer_ipl = 12U;
    dma_ctrl1.p_callback = DMA_user_callback;
    DMA_Open(&dma_ctrl1, &dma_cfg1);

    for(i = 0U; i < TEST_SIZE; i++)
    {
        src[i] = 'A' + (i % 26U);
    }

    for(i = 0U; i < TEST_SIZE; i++)
    {
        dest[i] = 0U;
    }

    DMA_Start(&dma_ctrl1, (uint32_t)&src, (uint32_t)&dest, TEST_SIZE);
    
    BSP_Software_Delay(BSP_DELAY_UNIT_MILLISECOND, 1U);

    DMA_Stop(&dma_ctrl1);
    DMA_Close(&dma_ctrl1);

    /* Verify the tranfer */
    for(i = 0U; i < TEST_SIZE; i++)
    {
        ASSERT(src[i] == dest[i]);
    }

    /* Verify the callback function */
    ASSERT(tranfer_irq_flag == 1U);

    /* Test case 2 */
    tranfer_irq_flag = 0U;
    half_tranfer_irq_flag = 0U;
    dma_cfg1.half_tranfer_ipl = 12U;
    dma_cfg1.tranfer_ipl = BSP_IRQ_DISABLE;
    dma_ctrl1.p_callback = DMA_user_callback;
    DMA_Open(&dma_ctrl1, &dma_cfg1);

    for(i = 0U; i < TEST_SIZE; i++)
    {
        src[i] = 'a' + (i % 26U);
    }

    for(i = 0U; i < TEST_SIZE; i++)
    {
        dest[i] = 0U;
    }

    DMA_Start(&dma_ctrl1, (uint32_t)&src, (uint32_t)&dest, TEST_SIZE);
    
    BSP_Software_Delay(BSP_DELAY_UNIT_MILLISECOND, 1U);

    /* Clear interrupt flag */
    dma_ctrl1.p_reg->IFCR |= 1U;

    DMA_Stop(&dma_ctrl1);
    DMA_Close(&dma_ctrl1);

    /* Verify the tranfer */
    for(i = 0U; i < TEST_SIZE; i++)
    {
        ASSERT(src[i] == dest[i]);
    }

    /* Verify the callback function */
    ASSERT(half_tranfer_irq_flag == 1U);

    /* Test case 3 */
    tranfer_irq_flag = 0U;
    half_tranfer_irq_flag = 0U;
    dma_cfg1.half_tranfer_ipl = BSP_IRQ_DISABLE;
    dma_cfg1.tranfer_ipl = BSP_IRQ_DISABLE;
    dma_cfg1.err_ipl = 12U;
    dma_ctrl1.p_callback = DMA_user_callback;

    DMA_Open(&dma_ctrl1, &dma_cfg1);

    DMA_Start(&dma_ctrl1, (uint32_t)&src, (uint32_t)0x00, TEST_SIZE);
    
    BSP_Software_Delay(BSP_DELAY_UNIT_MILLISECOND, 1U);

    DMA_Stop(&dma_ctrl1);
    DMA_Close(&dma_ctrl1);

    /* Verify the callback function */
    ASSERT(tranfer_error_irq_flag == 1U);

    /* Test case 4 */
    tranfer_irq_flag = 0U;
    half_tranfer_irq_flag = 0U;
    dma_cfg1.tranfer_ipl = 12U;
    dma_ctrl1.p_callback = DMA_user_callback;
    dma_cfg1.channel = 7U;
    DMA_Open(&dma_ctrl1, &dma_cfg1);

    for(i = 0U; i < TEST_SIZE; i++)
    {
        src[i] = 'A' + (i % 26U);
    }

    for(i = 0U; i < TEST_SIZE; i++)
    {
        dest[i] = 0U;
    }

    DMA_Start(&dma_ctrl1, (uint32_t)&src, (uint32_t)&dest, TEST_SIZE);
    
    BSP_Software_Delay(BSP_DELAY_UNIT_MILLISECOND, 1U);

    DMA_Stop(&dma_ctrl1);
    DMA_Close(&dma_ctrl1);

    /* Verify the tranfer */
    for(i = 0U; i < TEST_SIZE; i++)
    {
        ASSERT(src[i] == dest[i]);
    }

    /* Verify the callback function */
    ASSERT(tranfer_irq_flag == 1U);

    /* Test case 5 */
    tranfer_irq_flag = 0U;
    tranfer_irq_flag1 = 0U;

    dma_cfg1.tranfer_ipl = 12U;
    dma_ctrl1.p_callback = DMA_user_callback;
    dma_cfg1.channel = 4U;

    dma_cfg2.tranfer_ipl = 12U;
    dma_ctrl2.p_callback = DMA_user_callback_1;
    dma_cfg2.channel = 5U;

    DMA_Open(&dma_ctrl1, &dma_cfg1);
    DMA_Open(&dma_ctrl2, &dma_cfg2);

    for(i = 0U; i < TEST_SIZE; i++)
    {
        src[i] = 'A' + (i % 26U);
    }

    for(i = 0U; i < TEST_SIZE; i++)
    {
        dest[i] = 0U;
    }

    for(i = 0U; i < TEST_SIZE; i++)
    {
        src1[i] = 'A' + (i % 26U);
    }

    for(i = 0U; i < TEST_SIZE; i++)
    {
        dest1[i] = 0U;
    }

    DMA_Start(&dma_ctrl1, (uint32_t)&src, (uint32_t)&dest, TEST_SIZE);
    DMA_Start(&dma_ctrl2, (uint32_t)&src1, (uint32_t)&dest1, TEST_SIZE);
    
    BSP_Software_Delay(BSP_DELAY_UNIT_MILLISECOND, 1U);

    DMA_Stop(&dma_ctrl1);
    DMA_Close(&dma_ctrl1);
    DMA_Stop(&dma_ctrl2);
    DMA_Close(&dma_ctrl2);

    /* Verify the tranfer */
    for(i = 0U; i < TEST_SIZE; i++)
    {
        ASSERT(src[i] == dest[i]);
    }

    for(i = 0U; i < TEST_SIZE; i++)
    {
        ASSERT(src1[i] == dest1[i]);
    }

    /* Verify the callback function */
    ASSERT(tranfer_irq_flag == 1U);
    ASSERT(tranfer_irq_flag1 == 1U);
}

#if (BSP_FEATURE_DMA2_IS_AVAILABLE)
void dma2_mem_2_mem_test_case(void)
{
    uint16_t i;

    /* Test case 1 */
    tranfer_irq_flag = 0U;
    tranfer_irq_flag1 = 0U;

    dma_cfg1.channel = 1U;
    dma_cfg1.unit = DMA_UNIT_2;

    dma_cfg1.channel = 4U;
    dma_cfg2.channel = DMA_UNIT_2;

    DMA_Open(&dma_ctrl1, &dma_cfg1);
    DMA_Open(&dma_ctrl2, &dma_cfg2);

    for(i = 0U; i < TEST_SIZE; i++)
    {
        src[i] = 'A' + (i % 26U);
    }

    for(i = 0U; i < TEST_SIZE; i++)
    {
        dest[i] = 0U;
    }

    for(i = 0U; i < TEST_SIZE; i++)
    {
        src1[i] = 'A' + (i % 26U);
    }

    for(i = 0U; i < TEST_SIZE; i++)
    {
        dest1[i] = 0U;
    }

    DMA_Start(&dma_ctrl1, (uint32_t)&src, (uint32_t)&dest, TEST_SIZE);
    DMA_Start(&dma_ctrl2, (uint32_t)&src1, (uint32_t)&dest1, TEST_SIZE);
    
    BSP_Software_Delay(BSP_DELAY_UNIT_MILLISECOND, 1U);

    DMA_Stop(&dma_ctrl1);
    DMA_Close(&dma_ctrl1);
    DMA_Stop(&dma_ctrl2);
    DMA_Close(&dma_ctrl2);

    /* Verify the tranfer */
    for(i = 0U; i < TEST_SIZE; i++)
    {
        ASSERT(src[i] == dest[i]);
    }

    for(i = 0U; i < TEST_SIZE; i++)
    {
        ASSERT(src1[i] == dest1[i]);
    }

    /* Verify the callback function */
    ASSERT(tranfer_irq_flag == 1U);
    ASSERT(tranfer_irq_flag1 == 1U);
}
#endif

void dma_run_test(void)
{
    dma_mem_2_mem_test_case();
    dma_mem_2_mem_interrupt_test_case();
#if (BSP_FEATURE_DMA2_IS_AVAILABLE)
    dma2_mem_2_mem_test_case();
#endif
}

#endif
