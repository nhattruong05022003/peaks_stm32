#include "dma.h"

#define DMA_OPEN (0x00447741U) ///< DMA in ASCII

/* DMA unit array */
static DMAx_Type * dma_unit_list[] = 
{
    DMA1,
#if (BSP_FEATURE_DMA2_IS_AVAILABLE)
    DMA2
#endif
};

void DMA_Open(dma_ctrl_t *p_ctrl, const dma_cfg_t *p_cfg)
{
    ASSERT(p_ctrl);
    ASSERT(p_cfg);
#if (BSP_FEATURE_DMA2_IS_AVAILABLE)
    ASSERT(p_cfg->unit <= DMA_UNIT_2);
#else
    ASSERT(p_cfg->unit <= DMA_UNIT_1);
#endif

#if (BSP_FEATURE_DMA2_IS_AVAILABLE)
    if(p_cfg->unit == DMA_UNIT_1)
    {
        ASSERT((p_cfg->channel >= 1U) && (p_cfg->channel <= 7U));
    }
    else
    {
        ASSERT((p_cfg->channel >= 1U) && (p_cfg->channel <= 5U));
    }
#else
    ASSERT((p_cfg->channel >= 1U) && (p_cfg->channel <= 7U));
#endif

    ASSERT(!((p_cfg->configuration_b.m2m_mode == DMA_MEM2MEM_MODE_ENABLE) \
    && (p_cfg->configuration_b.circular_mode == DMA_CIRCULAR_MODE_ENABLE)));
    ASSERT(p_ctrl->open != DMA_OPEN);

    uint8_t channel = p_cfg->channel - 1U;

    p_ctrl->p_reg = dma_unit_list[(uint8_t) (p_cfg->unit)];
    p_ctrl->p_cfg = p_cfg;

    /* Set up circular mode */
    p_ctrl->p_reg->DMA_Channelx_Reg[channel].CCRx_b.CIRC = p_cfg->configuration_b.circular_mode;

    /* Set up peripheral increase mode */
    p_ctrl->p_reg->DMA_Channelx_Reg[channel].CCRx_b.PINC = p_cfg->configuration_b.periph_inc_mode;

    /* Set up memory increase mode */
    p_ctrl->p_reg->DMA_Channelx_Reg[channel].CCRx_b.MINC = p_cfg->configuration_b.mem_inc_mode;

    /* Set up memory to memory mode */
    p_ctrl->p_reg->DMA_Channelx_Reg[channel].CCRx_b.MEM2MEM = p_cfg->configuration_b.m2m_mode;

    /* Set up peripheral size */
    p_ctrl->p_reg->DMA_Channelx_Reg[channel].CCRx_b.PSIZE = p_cfg->configuration_b.periph_size;

    /* Set up memory size */
    p_ctrl->p_reg->DMA_Channelx_Reg[channel].CCRx_b.MSIZE = p_cfg->configuration_b.mem_size;

    /* Set up DMA priority */
    p_ctrl->p_reg->DMA_Channelx_Reg[channel].CCRx_b.PL = p_cfg->configuration_b.channel_priority;

    /* Set up Tranfer Interrupt */
    if(p_cfg->tranfer_ipl != BSP_IRQ_DISABLE)
    {
        IRQn_t irq_num;
        p_ctrl->p_reg->DMA_Channelx_Reg[channel].CCRx_b.TCIE = 1U;
        if(p_cfg->unit == DMA_UNIT_2)
        {
            if(p_cfg->channel >= 4U)
            {
                irq_num = (IRQn_t)(DMA2_Channel1_IRQHandler_IRQ_Num + 3);
            }
            else
            {
                irq_num = (IRQn_t)(DMA2_Channel1_IRQHandler_IRQ_Num + ((IRQn_t)p_cfg->channel - 1));
            }
        }
        else
        {
            irq_num = (IRQn_t)(DMA1_Channel1_IRQHandler_IRQ_Num + ((IRQn_t)p_cfg->channel - 1));
        }
        BSP_IRQ_Enable(irq_num);
        BSP_IRQ_SetPriority(irq_num, p_cfg->tranfer_ipl);
        BSP_IRQ_SetContext(irq_num, (void *)p_ctrl);
    }

    /* Set up Half-Tranfer Interrupt */
    if(p_cfg->half_tranfer_ipl != BSP_IRQ_DISABLE)
    {
        IRQn_t irq_num;
        p_ctrl->p_reg->DMA_Channelx_Reg[channel].CCRx_b.HTIE = 1U;
        if(p_cfg->unit == DMA_UNIT_2)
        {
            if(p_cfg->channel >= 4U)
            {
                irq_num = (IRQn_t)(DMA2_Channel1_IRQHandler_IRQ_Num + 3);
            }
            else
            {
                irq_num = (IRQn_t)(DMA2_Channel1_IRQHandler_IRQ_Num + ((IRQn_t)p_cfg->channel - 1));
            }
        }
        else
        {
            irq_num = (IRQn_t)(DMA1_Channel1_IRQHandler_IRQ_Num + ((IRQn_t)p_cfg->channel - 1));
        }
        BSP_IRQ_Enable(irq_num);
        BSP_IRQ_SetPriority(irq_num, p_cfg->half_tranfer_ipl);
        BSP_IRQ_SetContext(irq_num, (void *)p_ctrl);
    }

    /* Set up Error Interrupt */
    if(p_cfg->err_ipl != BSP_IRQ_DISABLE)
    {
        IRQn_t irq_num;
        p_ctrl->p_reg->DMA_Channelx_Reg[channel].CCRx_b.TEIE = 1U;
        if(p_cfg->unit == DMA_UNIT_2)
        {
            if(p_cfg->channel >= 4U)
            {
                irq_num = (IRQn_t)(DMA2_Channel1_IRQHandler_IRQ_Num + 3);
            }
            else
            {
                irq_num = (IRQn_t)(DMA2_Channel1_IRQHandler_IRQ_Num + ((IRQn_t)p_cfg->channel - 1));
            }
        }
        else
        {
            irq_num = (IRQn_t)(DMA1_Channel1_IRQHandler_IRQ_Num + ((IRQn_t)p_cfg->channel - 1));
        }
        BSP_IRQ_Enable(irq_num);
        BSP_IRQ_SetPriority(irq_num, p_cfg->half_tranfer_ipl);
        BSP_IRQ_SetContext(irq_num, (void *)p_ctrl);
    }

    p_ctrl->open = DMA_OPEN;
}

void DMA_Start(dma_ctrl_t *p_ctrl, const uint32_t src_address, const uint32_t dest_address, uint16_t size)
{
    ASSERT(p_ctrl);
    uint8_t channel = p_ctrl->p_cfg->channel - 1U;

    /* Set up tranfer size */
    p_ctrl->p_reg->DMA_Channelx_Reg[channel].CNDTRx = size;

    /* Set up source address */
    p_ctrl->p_reg->DMA_Channelx_Reg[channel].CPARx = (uint32_t) src_address;

    /* Set up destination address */
    p_ctrl->p_reg->DMA_Channelx_Reg[channel].CMARx = (uint32_t) dest_address;

    /* Enable DMA channel */
    p_ctrl->p_reg->DMA_Channelx_Reg[channel].CCRx_b.EN = 1U;
}

void DMA_Stop(dma_ctrl_t *p_ctrl)
{
    ASSERT(p_ctrl);
    uint8_t channel = p_ctrl->p_cfg->channel - 1U;

    /* Clear tranfer size */
    p_ctrl->p_reg->DMA_Channelx_Reg[channel].CNDTRx = 0U;

    /* Clear source address */
    p_ctrl->p_reg->DMA_Channelx_Reg[channel].CPARx = (uint32_t) 0U;

    /* Clear destination address */
    p_ctrl->p_reg->DMA_Channelx_Reg[channel].CMARx = (uint32_t) 0U;

    /* Disable DMA channel */
    p_ctrl->p_reg->DMA_Channelx_Reg[channel].CCRx_b.EN = 0U;
}

void DMA_Close(dma_ctrl_t *p_ctrl)
{
    ASSERT(p_ctrl);
    ASSERT(p_ctrl->open == DMA_OPEN);

    const dma_cfg_t *p_cfg = p_ctrl->p_cfg; 
    uint8_t channel = p_cfg->channel - 1U;

    /* Clear circular mode */
    p_ctrl->p_reg->DMA_Channelx_Reg[channel].CCRx_b.CIRC = 0U;

    /* Clear peripheral increase mode */
    p_ctrl->p_reg->DMA_Channelx_Reg[channel].CCRx_b.PINC = 0U;

    /* Clear memory increase mode */
    p_ctrl->p_reg->DMA_Channelx_Reg[channel].CCRx_b.MINC = 0U;

    /* Clear memory to memory mode */
    p_ctrl->p_reg->DMA_Channelx_Reg[channel].CCRx_b.MEM2MEM = 0U;

    /* Clear peripheral size */
    p_ctrl->p_reg->DMA_Channelx_Reg[channel].CCRx_b.PSIZE = 0U;

    /* Clear memory size */
    p_ctrl->p_reg->DMA_Channelx_Reg[channel].CCRx_b.MSIZE = 0U;

    /* Clear DMA priority */
    p_ctrl->p_reg->DMA_Channelx_Reg[channel].CCRx_b.PL = 0U;

    /* Set up Tranfer Interrupt */
    if(p_cfg->tranfer_ipl != BSP_IRQ_DISABLE)
    {
        IRQn_t irq_num;
        p_ctrl->p_reg->DMA_Channelx_Reg[channel].CCRx_b.TCIE = 0U;
        if(p_cfg->unit == DMA_UNIT_2)
        {
            if(p_cfg->channel >= 4U)
            {
                irq_num = (IRQn_t)(DMA2_Channel1_IRQHandler_IRQ_Num + 3);
            }
            else
            {
                irq_num = (IRQn_t)(DMA2_Channel1_IRQHandler_IRQ_Num + ((IRQn_t)p_cfg->channel - 1));
            }
        }
        else
        {
            irq_num = (IRQn_t)(DMA1_Channel1_IRQHandler_IRQ_Num + ((IRQn_t)p_cfg->channel - 1));
        }
        BSP_IRQ_Disable(irq_num);
        BSP_IRQ_SetContext(irq_num, NULL);
    }

    /* Set up Half-Tranfer Interrupt */
    if(p_cfg->half_tranfer_ipl != BSP_IRQ_DISABLE)
    {
        IRQn_t irq_num;
        p_ctrl->p_reg->DMA_Channelx_Reg[channel].CCRx_b.HTIE = 0U;
        if(p_cfg->unit == DMA_UNIT_2)
        {
            if(p_cfg->channel >= 4U)
            {
                irq_num = (IRQn_t)(DMA2_Channel1_IRQHandler_IRQ_Num + 3);
            }
            else
            {
                irq_num = (IRQn_t)(DMA2_Channel1_IRQHandler_IRQ_Num + ((IRQn_t)p_cfg->channel - 1));
            }
        }
        else
        {
            irq_num = (IRQn_t)(DMA1_Channel1_IRQHandler_IRQ_Num + ((IRQn_t)p_cfg->channel - 1));
        }
        BSP_IRQ_Disable(irq_num);
        BSP_IRQ_SetContext(irq_num, NULL);
    }

    /* Set up Error Interrupt */
    if(p_cfg->err_ipl != BSP_IRQ_DISABLE)
    {
        IRQn_t irq_num;
        p_ctrl->p_reg->DMA_Channelx_Reg[channel].CCRx_b.TEIE = 0U;
        if(p_cfg->unit == DMA_UNIT_2)
        {
            if(p_cfg->channel >= 4U)
            {
                irq_num = (IRQn_t)(DMA2_Channel1_IRQHandler_IRQ_Num + 3);
            }
            else
            {
                irq_num = (IRQn_t)(DMA2_Channel1_IRQHandler_IRQ_Num + ((IRQn_t)p_cfg->channel - 1));
            }
        }
        else
        {
            irq_num = (IRQn_t)(DMA1_Channel1_IRQHandler_IRQ_Num + ((IRQn_t)p_cfg->channel - 1));
        }
        BSP_IRQ_Disable(irq_num);
        BSP_IRQ_SetContext(irq_num, NULL);
    }

    /* Clear interrupt flag */
    p_ctrl->p_reg->IFCR |= (0x0FU) << ((channel * 4U) + 1U);

    p_ctrl->p_callback = NULL;
    p_ctrl->p_cfg = NULL;
    p_ctrl->p_reg = NULL;
    p_ctrl->open = 0U;
}

void DMA_IRQHandler(void)
{
    /* Get Irq Number */
    IRQn_t irq = BSP_IRQ_GetIRQNumber();

    dma_ctrl_t *p_ctrl = (dma_ctrl_t *) BSP_IRQ_GetContext(irq);
    uint8_t channel = p_ctrl->p_cfg->channel - 1U;

    if((p_ctrl->p_reg->ISR & DMA_HALF_TRANFER_IRQ_FLAG(channel)) && \
        (p_ctrl->p_reg->DMA_Channelx_Reg[channel].CCRx_b.HTIE))
    {
        if(p_ctrl->p_callback != NULL)
        {
            p_ctrl->p_callback((void *) p_ctrl);
        }

        p_ctrl->p_reg->IFCR |= DMA_HALF_TRANFER_IRQ_FLAG(channel);
    }

    if((p_ctrl->p_reg->ISR & DMA_TRANFER_IRQ_FLAG(channel)) && \
        (p_ctrl->p_reg->DMA_Channelx_Reg[channel].CCRx_b.TCIE))
    {
        if(p_ctrl->p_callback != NULL)
        {
            p_ctrl->p_callback((void *) p_ctrl);
        }

        p_ctrl->p_reg->IFCR |= DMA_TRANFER_IRQ_FLAG(channel);
        p_ctrl->p_reg->IFCR |= DMA_HALF_TRANFER_IRQ_FLAG(channel);
    }

    if((p_ctrl->p_reg->ISR & DMA_TRANFER_ERROR_IRQ_FLAG(channel)) && \
        (p_ctrl->p_reg->DMA_Channelx_Reg[channel].CCRx_b.TEIE))
    {
        if(p_ctrl->p_callback != NULL)
        {
            p_ctrl->p_callback((void *) p_ctrl);
        }

        p_ctrl->p_reg->IFCR |= DMA_TRANFER_ERROR_IRQ_FLAG(channel);
    }
}
