#include "spi.h"

#define SPI_OPEN (0x00535049U) ///< SPI in ASCII

/** SPI unit array */
static SPIx_Type * spi_unit_list[] = 
{
    SPI1,
    SPI2,
#if (BSP_FEATURE_SPI3_IS_AVAILABLE)
    SPI3
#endif
};

static void spi_txi_isr(void * p_ctrl_arg);
static void spi_rxi_isr(void * p_ctrl_arg);
static void spi_eri_isr(void * p_ctrl_arg);

/** SPI isr function pointer array */
static void (*spi_isr_funcion[])(void * p_ctrl_arg) =
{
    spi_rxi_isr,
    spi_txi_isr,
    spi_eri_isr
};

/**********************************************************************************************************************
 * @brief Configures the SPI with the specified configuration.
 *
 * @param p_ctrl  Pointer to the SPI control structure.
 * @param p_cfg   Pointer to the SPI configuration structure.
 *
 * @return None.
 *********************************************************************************************************************/
void SPI_Open(spi_ctrl_t *p_ctrl, const spi_cfg_t *p_cfg)
{
    ASSERT(p_ctrl);
    ASSERT(p_cfg);
    ASSERT((uint8_t)p_cfg->unit < (uint8_t)sizeof(spi_unit_list));
    ASSERT(p_ctrl->open != SPI_OPEN);

    p_ctrl->p_reg = spi_unit_list[(uint8_t) p_cfg->unit];
    p_ctrl->p_cfg = p_cfg;

    /* Config baud rate */
    p_ctrl->p_reg->SPI_CR1_b.BR = p_cfg->configuration_b.baud_rate;

    /* Config CPOL and CPHA */
    p_ctrl->p_reg->SPI_CR1 |= p_cfg->configuration_b.data_mode;

    /* Config data frame */
    p_ctrl->p_reg->SPI_CR1_b.DFF = p_cfg->configuration_b.data_frame;

    /* Config frame */
    p_ctrl->p_reg->SPI_CR1_b.LSBFIRST = p_cfg->configuration_b.frame_format;

    /* Config hardware CRC */
    p_ctrl->p_reg->SPI_CR1_b.CRCEN = p_cfg->configuration_b.crc_en;

    /* Config direction */
    p_ctrl->p_reg->SPI_CR1_b.BIDIMODE = 0U;
    p_ctrl->p_reg->SPI_CR1_b.BIDIOE = 0U;
    p_ctrl->p_reg->SPI_CR1_b.RXONLY = 0U;
    p_ctrl->p_reg->SPI_CR1 |= p_cfg->direction;

    /* Config software slave management */
    if(SPI_SOFTWARE_SLAVE_MANAGE_ENABLE == p_cfg->configuration_b.soft_slave_en)
    {
        p_ctrl->p_reg->SPI_CR1_b.SSM = SPI_SOFTWARE_SLAVE_MANAGE_ENABLE;
        p_ctrl->p_reg->SPI_CR1_b.SSI = p_cfg->configuration_b.mode;
    }
    else
    {
        /* In this mode, need external voltage to tell hardware that it's master or pull to GND to tell that it is slave */
        p_ctrl->p_reg->SPI_CR1_b.SSM = SPI_SOFTWARE_SLAVE_MANAGE_DISABLE; 
    }

    /* Config slave select mode */
    p_ctrl->p_reg->SPI_CR2_b.SSOE = p_cfg->configuration_b.slave_select_mode;

    /* Set up transmit interrupt */
    if(p_cfg->transmit_ipl != BSP_IRQ_DISABLE)
    {
        IRQn_t irq_num = (IRQn_t)p_cfg->unit + SPI1_IRQHandler_IRQ_Num;
        BSP_IRQ_Enable(irq_num);
        BSP_IRQ_SetPriority(irq_num, p_cfg->transmit_ipl);
        BSP_IRQ_SetContext(irq_num, (void *)p_ctrl);
    }

    /* Set up receive interrupt */
    if(p_cfg->receive_ipl != BSP_IRQ_DISABLE)
    {
        IRQn_t irq_num = (IRQn_t)p_cfg->unit + SPI1_IRQHandler_IRQ_Num;
        p_ctrl->p_reg->SPI_CR2_b.RXNEIE = 1U;
        BSP_IRQ_Enable(irq_num);
        BSP_IRQ_SetPriority(irq_num, p_cfg->receive_ipl);
        BSP_IRQ_SetContext(irq_num, (void *)p_ctrl);
    }

    /* Set up error interrupt */
    if(p_cfg->err_ipl != BSP_IRQ_DISABLE)
    {
        IRQn_t irq_num = (IRQn_t)p_cfg->unit + SPI1_IRQHandler_IRQ_Num;
        p_ctrl->p_reg->SPI_CR2_b.ERRIE = 1U;
        BSP_IRQ_Enable(irq_num);
        BSP_IRQ_SetPriority(irq_num, p_cfg->err_ipl);
        BSP_IRQ_SetContext(irq_num, (void *)p_ctrl);
    }

    /* Set up DMA for SPI */
    /* When using DMA it's recommended to use IRQ of DMA instead of SPI */
    if(p_ctrl->p_cfg->configuration_b.dma_transmit_en)
    {
        ASSERT(p_ctrl->p_cfg->p_dma_tx_cfg);
        ASSERT(p_ctrl->p_cfg->p_dma_tx_ctrl);

        DMA_Open(p_ctrl->p_cfg->p_dma_tx_ctrl, p_ctrl->p_cfg->p_dma_tx_cfg);
    }

    if(p_ctrl->p_cfg->configuration_b.dma_receive_en)
    {
        ASSERT(p_ctrl->p_cfg->p_dma_rx_cfg);
        ASSERT(p_ctrl->p_cfg->p_dma_rx_ctrl);

        DMA_Open(p_ctrl->p_cfg->p_dma_rx_ctrl, p_ctrl->p_cfg->p_dma_rx_cfg);
    }

    /* Config mode for SPI */
    p_ctrl->p_reg->SPI_CR1_b.MSTR = p_cfg->configuration_b.mode;

    /* Enable SPI */
    p_ctrl->p_reg->SPI_CR1_b.SPE = 1U;

    /* Dummy read for data register */
    (void)p_ctrl->p_reg->SPI_DR;

    p_ctrl->callback_status = SPI_CALLBACK_STATUS_NONE;

    p_ctrl->open = SPI_OPEN;
}

/**********************************************************************************************************************
 * @brief Sets the user-defined callback function for SPI interrupt events.
 *
 * @param p_ctrl      Pointer to the SPI control structure.
 * @param p_callback  Pointer to the user callback function.
 *
 * @return None.
 *********************************************************************************************************************/
void SPI_CallbackSet(spi_ctrl_t *p_ctrl, void (*p_callback)(void *p_args))
{
    ASSERT(p_ctrl);
    ASSERT(p_ctrl->open == SPI_OPEN);

    p_ctrl->p_callback = p_callback;
}

/**********************************************************************************************************************
 * @brief Transmits data over SPI using an interrupt-driven mechanism.
 *
 * @param p_ctrl  Pointer to the SPI control structure.
 * @param p_src   Pointer to the buffer containing the data to be transmitted.
 * @param size    Number of bytes to transmit.
 *
 * @return None.
 *********************************************************************************************************************/
void SPI_Write(spi_ctrl_t *p_ctrl, void * p_src, uint16_t size)
{
    ASSERT(p_ctrl);
    ASSERT(p_ctrl->open == SPI_OPEN);
    ASSERT(p_src);

    if(p_ctrl->p_cfg->configuration_b.dma_transmit_en)
    {
        DMAx_Type *dma_unit = dma_unit_list[(uint8_t)((dma_cfg_t *)(p_ctrl->p_cfg->p_dma_tx_cfg))->unit];
        uint8_t channel = ((dma_cfg_t *)(p_ctrl->p_cfg->p_dma_tx_cfg))->channel - 1U;

        /* Set up tranfer size */
        dma_unit->DMA_Channelx_Reg[channel].CNDTRx = size;

        /* Set up source address */
        dma_unit->DMA_Channelx_Reg[channel].CPARx = (uint32_t) &(p_ctrl->p_reg->SPI_DR);

        /* Set up destination address */
        dma_unit->DMA_Channelx_Reg[channel].CMARx = (uint32_t) p_src;

        p_ctrl->p_reg->SPI_CR2_b.TXDMAEN = 1U;

        dma_unit->DMA_Channelx_Reg[channel].CCRx_b.EN = 1U;
    }
    else
    {
        p_ctrl->p_src = p_src;
        p_ctrl->write_size = size;

        p_ctrl->p_reg->SPI_CR2_b.TXEIE = 1U;
    }
}

/**********************************************************************************************************************
 * @brief Receives data over SPI using an interrupt-driven mechanism.
 *
 * @param p_ctrl  Pointer to the SPI control structure.
 * @param p_dest  Pointer to the buffer containing the data to be received.
 * @param size    Number of bytes to be received.
 *
 * @return None.
 *********************************************************************************************************************/
void SPI_Read(spi_ctrl_t *p_ctrl, void * p_dest, uint16_t size)
{
    ASSERT(p_ctrl);
    ASSERT(p_ctrl->open == SPI_OPEN);
    ASSERT(p_dest);

    if(p_ctrl->p_cfg->configuration_b.dma_receive_en)
    {
        DMAx_Type *dma_unit = dma_unit_list[(uint8_t)((dma_cfg_t *)(p_ctrl->p_cfg->p_dma_rx_cfg))->unit];
        uint8_t channel = ((dma_cfg_t *)(p_ctrl->p_cfg->p_dma_rx_cfg))->channel - 1U;

        /* Set up tranfer size */
        dma_unit->DMA_Channelx_Reg[channel].CNDTRx = size;

        /* Set up source address */
        dma_unit->DMA_Channelx_Reg[channel].CPARx = (uint32_t) &(p_ctrl->p_reg->SPI_DR);

        /* Set up destination address */
        dma_unit->DMA_Channelx_Reg[channel].CMARx = (uint32_t) p_dest;

        p_ctrl->p_reg->SPI_CR2_b.RXDMAEN = 1U;

        dma_unit->DMA_Channelx_Reg[channel].CCRx_b.EN = 1U;
    }
    else
    {
        p_ctrl->p_dest = p_dest;
        p_ctrl->read_size = size;

        /* If it's in Master mode, write dummy value to generate clock for slave */
        if(p_ctrl->p_cfg->configuration_b.mode == SPI_MODE_MASTER)
        {
            p_ctrl->p_reg->SPI_DR = 0xAAU; /* Dummy to generate clock */
        }
    }
}

/**********************************************************************************************************************
 * @brief Transmit data with polling mode.
 *
 * @return None
 *********************************************************************************************************************/
void SPI_PollingWrite (spi_ctrl_t *p_ctrl, void *data)
{
    while(p_ctrl->p_reg->SPI_SR_b.TXE == 0U);
    if(p_ctrl->p_cfg->configuration_b.data_frame == SPI_DATA_FRAME_FORMAT_8_BITS)
        p_ctrl->p_reg->SPI_DR = *(volatile uint8_t *)data;
    else
        p_ctrl->p_reg->SPI_DR = *(volatile uint16_t *)data;
}

/**********************************************************************************************************************
 * @brief Receive data with polling mode.
 *
 * @return None
 *********************************************************************************************************************/
void SPI_PollingRead (spi_ctrl_t *p_ctrl, void *data)
{
    while(p_ctrl->p_reg->SPI_SR_b.RXNE == 0U);
    if(p_ctrl->p_cfg->configuration_b.data_frame == SPI_DATA_FRAME_FORMAT_8_BITS)
        *(volatile uint8_t *)data = p_ctrl->p_reg->SPI_DR;
    else
        *(volatile uint16_t *)data = p_ctrl->p_reg->SPI_DR;
}

/**********************************************************************************************************************
 * @brief Deconfigures the SPI.
 *
 * @param p_ctrl  Pointer to the SPI control structure.
 *
 * @return None.
 *********************************************************************************************************************/
void SPI_Close(spi_ctrl_t *p_ctrl)
{
    ASSERT(p_ctrl);
    ASSERT(p_ctrl->p_cfg);
    ASSERT(p_ctrl->open == SPI_OPEN);

    const spi_cfg_t *p_cfg = p_ctrl->p_cfg;

    /* Disable SPI */
    p_ctrl->p_reg->SPI_CR1_b.SPE = 0U;

    /* Clear CRC error flag */
    p_ctrl->p_reg->SPI_SR_b.CRCERR = 0U;

    /* Dummy read for Data register */
    (void)p_ctrl->p_reg->SPI_DR;

    /* Clear transmit interrupt */
    if(p_cfg->transmit_ipl != BSP_IRQ_DISABLE)
    {
        IRQn_t irq_num = (IRQn_t)p_cfg->unit + SPI1_IRQHandler_IRQ_Num;
        p_ctrl->p_reg->SPI_CR2_b.TXEIE = 0U;
        BSP_IRQ_Disable(irq_num);
        BSP_IRQ_SetContext(irq_num, NULL);
    }

    /* Clear receive interrupt */
    if(p_cfg->receive_ipl != BSP_IRQ_DISABLE)
    {
        IRQn_t irq_num = (IRQn_t)p_cfg->unit + SPI1_IRQHandler_IRQ_Num;
        p_ctrl->p_reg->SPI_CR2_b.RXNEIE = 0U;
        BSP_IRQ_Disable(irq_num);
        BSP_IRQ_SetContext(irq_num, NULL);
    }

    /* Clear error interrupt */
    if(p_cfg->err_ipl != BSP_IRQ_DISABLE)
    {
        IRQn_t irq_num = (IRQn_t)p_cfg->unit + SPI1_IRQHandler_IRQ_Num;
        p_ctrl->p_reg->SPI_CR2_b.ERRIE = 0U;
        BSP_IRQ_Disable(irq_num);
        BSP_IRQ_SetContext(irq_num, NULL);
    }

    /* Clear DMA for SPI */
    if(p_ctrl->p_cfg->configuration_b.dma_transmit_en)
    {
        ASSERT(p_ctrl->p_cfg->p_dma_tx_ctrl);

        p_ctrl->p_reg->SPI_CR2_b.TXDMAEN = 0U;

        DMA_Stop(p_ctrl->p_cfg->p_dma_tx_ctrl);
        DMA_Close(p_ctrl->p_cfg->p_dma_tx_ctrl);
    }

    if(p_ctrl->p_cfg->configuration_b.dma_receive_en)
    {
        ASSERT(p_ctrl->p_cfg->p_dma_rx_ctrl);

        p_ctrl->p_reg->SPI_CR2_b.RXDMAEN = 0U;

        DMA_Stop(p_ctrl->p_cfg->p_dma_rx_ctrl);
        DMA_Close(p_ctrl->p_cfg->p_dma_rx_ctrl);
    }

    /* Clear baud rate */
    p_ctrl->p_reg->SPI_CR1_b.BR = 0x00U;

    /* Clear CPOL and CPHA */
    p_ctrl->p_reg->SPI_CR1 &= ~(0x03U);

    /* Clear data frame */
    p_ctrl->p_reg->SPI_CR1_b.DFF = 0x00U;

    /* Clear frame */
    p_ctrl->p_reg->SPI_CR1_b.LSBFIRST = 0x00U;

    /* Clear hardware CRC */
    p_ctrl->p_reg->SPI_CR1_b.CRCEN = SPI_HARDWARE_CRC_DISABLE;

    /* Clear direction (Clear bit 10, 14, 15)*/
    p_ctrl->p_reg->SPI_CR1 &= ~((1U << 15) | (1U << 14) | (1U << 10));

    /* Clear software slave management */
    p_ctrl->p_reg->SPI_CR1_b.SSM = SPI_SOFTWARE_SLAVE_MANAGE_DISABLE;
    p_ctrl->p_reg->SPI_CR1_b.SSI = 0x00U;

    /* Clear slave select mode */
    p_ctrl->p_reg->SPI_CR2_b.SSOE = 0x00U;

    /* Clear CRC polynomial */
    p_ctrl->p_reg->SPI_CRCPR = 0x07U;

    /* Clear mode for SPI */
    p_ctrl->p_reg->SPI_CR1_b.MSTR = 0x00U;

    /* Clear all the elements of control struct */
    p_ctrl->callback_status = SPI_CALLBACK_STATUS_NONE;
    p_ctrl->p_callback = NULL;
    p_ctrl->p_cfg = NULL;
    p_ctrl->p_reg = NULL;
    p_ctrl->p_src = NULL;
    p_ctrl->p_dest = NULL;
    p_ctrl->write_size = 0U;
    p_ctrl->read_size = 0U;
    p_ctrl->open = 0x00U;
}

/**********************************************************************************************************************
 * @brief Handles SPI interrupt events.
 *
 * This interrupt service routine (ISR) processes SPI interrupt flags and performs
 * the required actions such as transmitting, receiving data or handling errors.
 *
 * @return None.
 *********************************************************************************************************************/
void SPI_IRQHandler(void)
{
    /* Get Irq Number */
    IRQn_t irq = BSP_IRQ_GetIRQNumber();

    spi_ctrl_t *p_ctrl = (spi_ctrl_t *) BSP_IRQ_GetContext(irq);

    uint8_t highest_priority = BSP_IRQ_DISABLE;
    uint8_t spi_isr_funcion_index = 0U;

    if((highest_priority > p_ctrl->p_cfg->receive_ipl) && (p_ctrl->p_reg->SPI_SR_b.RXNE))
    {
        highest_priority = p_ctrl->p_cfg->receive_ipl;
        spi_isr_funcion_index = 0U;
    }

    if((highest_priority > p_ctrl->p_cfg->transmit_ipl) && (p_ctrl->p_reg->SPI_SR_b.TXE) && (p_ctrl->p_reg->SPI_CR2_b.TXEIE))
    {
        highest_priority = p_ctrl->p_cfg->transmit_ipl;
        spi_isr_funcion_index = 1U;
    }

    if((highest_priority > p_ctrl->p_cfg->err_ipl) && (p_ctrl->p_reg->SPI_CR2_b.ERRIE) && \
        ((p_ctrl->p_reg->SPI_SR_b.OVR || p_ctrl->p_reg->SPI_SR_b.MODF || p_ctrl->p_reg->SPI_SR_b.CRCERR)))
    {
        highest_priority = p_ctrl->p_cfg->err_ipl;
        spi_isr_funcion_index = 2U;
    }

    spi_isr_funcion[spi_isr_funcion_index]((void *) p_ctrl);
}

/**********************************************************************************************************************
 * @brief Handles SPI transmit interrupt events.
 *
 * @return None.
 *********************************************************************************************************************/
static void spi_txi_isr(void * p_ctrl_arg)
{
    spi_ctrl_t *p_ctrl = (spi_ctrl_t *) p_ctrl_arg;

    if(p_ctrl->write_size != 0U)
    {
        if(p_ctrl->p_cfg->configuration_b.data_frame == SPI_DATA_FRAME_FORMAT_8_BITS)
        {
            p_ctrl->p_reg->SPI_DR = *(volatile uint8_t *) p_ctrl->p_src;
            __DMB(); /* Ensure that the data was finished writing to SPI_DR register */

            /* Trigge CRC transmit */
            if((p_ctrl->write_size == 0U) && (p_ctrl->p_cfg->configuration_b.crc_en))
            {
                p_ctrl->p_reg->SPI_CR1_b.CRCNEXT = 1U;
            }
            p_ctrl->p_src += 1U;
            p_ctrl->write_size -= 1U;
        }
        else
        {
            p_ctrl->p_reg->SPI_DR = *(volatile uint16_t *) p_ctrl->p_src;
            __DMB(); /* Ensure that the data was finished writing to SPI_DR register */

            /* Trigge CRC transmit */
            if((p_ctrl->write_size == 0U) && (p_ctrl->p_cfg->configuration_b.crc_en))
            {
                p_ctrl->p_reg->SPI_CR1_b.CRCNEXT = 1U;
            }
            p_ctrl->p_src += 2U;
            p_ctrl->write_size -= 2U;
        }

        if(p_ctrl->write_size == 0U)
        {
            p_ctrl->callback_status = SPI_CALLBACK_STATUS_TRANSMIT_COMPLETE;
            if(p_ctrl->p_callback != NULL)
            {
                p_ctrl->p_callback((void *) p_ctrl);
            }
            p_ctrl->p_reg->SPI_CR2_b.TXEIE = 0U;
        }
    }
}

/**********************************************************************************************************************
 * @brief Handles SPI receive interrupt events.
 *
 * @return None.
 *********************************************************************************************************************/
static void spi_rxi_isr(void * p_ctrl_arg)
{
    spi_ctrl_t *p_ctrl = (spi_ctrl_t *) p_ctrl_arg;

    if(p_ctrl->read_size != 0U)
    {
        if(p_ctrl->p_cfg->configuration_b.data_frame == SPI_DATA_FRAME_FORMAT_8_BITS)
        {
            *(volatile uint8_t *) p_ctrl->p_dest = p_ctrl->p_reg->SPI_DR;
            __DMB(); /* Ensure that the data was finished reading from SPI_DR register */

            p_ctrl->p_dest += 1U;
            p_ctrl->read_size -= 1U;
        }
        else
        {
            *(volatile uint16_t *) p_ctrl->p_dest = p_ctrl->p_reg->SPI_DR;
            __DMB(); /* Ensure that the data was finished reading from SPI_DR register */

            p_ctrl->p_dest += 2U;
            p_ctrl->read_size -= 2U;
        }

        if(p_ctrl->read_size == 0U)
        {
            p_ctrl->callback_status = SPI_CALLBACK_STATUS_RECEIVE_COMPLETE;
            if(p_ctrl->p_callback != NULL)
            {
                p_ctrl->p_callback((void *) p_ctrl);
            }
        }
        /* If it's in Master mode, write dummy value to generate clock for slave */
        else if(p_ctrl->p_cfg->configuration_b.mode == SPI_MODE_MASTER)
        {
            p_ctrl->p_reg->SPI_DR = 0xAAU; /* Dummy to generate clock */
        }
        else
        {
            /* Do nothing */
        } 
    }
    else
    {
        /* Perform dummy read */
        (void)p_ctrl->p_reg->SPI_DR;
    }
}

/**********************************************************************************************************************
 * @brief Handles SPI error interrupt events.
 *
 * @return None.
 *********************************************************************************************************************/
static void spi_eri_isr(void * p_ctrl_arg)
{
    spi_ctrl_t *p_ctrl = (spi_ctrl_t *) p_ctrl_arg;
    uint8_t error_status = p_ctrl->p_reg->SPI_SR;

    if((error_status & SPI_ERROR_OVERRUN_BIT_MASK))
    {
        uint16_t dummy_read;
        /* Dummy read to SPI_SR and SPI_DR */
        dummy_read = p_ctrl->p_reg->SPI_SR;

        dummy_read = p_ctrl->p_reg->SPI_DR;

        (void) dummy_read;

        p_ctrl->callback_status = SPI_CALLBACK_STATUS_OVERRUN;
        if(p_ctrl->p_callback != NULL)
        {
            p_ctrl->p_callback((void *) p_ctrl);
        }
    }
    else if((error_status & SPI_ERROR_MODE_FAULT_BIT_MASK))
    {
        uint16_t dummy_read;
        /* Dummy read to SPI_SR */
        dummy_read = p_ctrl->p_reg->SPI_SR;

        (void) dummy_read;

        p_ctrl->p_reg->SPI_CR1_b.MSTR = 1U;
        p_ctrl->p_reg->SPI_CR1_b.SPE = 1U;

        p_ctrl->callback_status = SPI_CALLBACK_STATUS_MASTER_MODE_FAULT;
        if(p_ctrl->p_callback != NULL)
        {
            p_ctrl->p_callback((void *) p_ctrl);
        }
    }
    else if((error_status & SPI_ERROR_CRC_BIT_MASK))
    {
        /* Clear CRCERR flag */
        p_ctrl->p_reg->SPI_SR_b.CRCERR = 0U;
        p_ctrl->callback_status = SPI_CALLBACK_STATUS_CRC_ERROR;
        if(p_ctrl->p_callback != NULL)
        {
            p_ctrl->p_callback((void *) p_ctrl);
        }
    }
    else
    {
        /* Do nothing */
    }
}
