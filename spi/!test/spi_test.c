#include "main.h"

#if (RUN_SPI_TEST_CASE)

static void spi_test_set_up_spi1_master_spi2_slave(void)
{
    /* Config pin for SPI 1 */
    /* Config NSS */
    BSP_IO_Configurate(BSP_IO_PORTA_PIN_4, BSP_IO_CONFIG_OUTPUT_GPIO_PUSH_PULL | BSP_IO_MODE_OUTPUT_50MHZ | BSP_IO_OUTPUT_INIT_STATE_HIGH);

    /* Config SCK */
    BSP_IO_Configurate(BSP_IO_PORTA_PIN_5, BSP_IO_CONFIG_OUTPUT_ALTER_PUSH_PULL | BSP_IO_MODE_OUTPUT_50MHZ | BSP_IO_OUTPUT_INIT_STATE_HIGH);

    /* Config MOSI */
    BSP_IO_Configurate(BSP_IO_PORTA_PIN_7, BSP_IO_CONFIG_OUTPUT_ALTER_PUSH_PULL | BSP_IO_MODE_OUTPUT_50MHZ | BSP_IO_OUTPUT_INIT_STATE_HIGH);

    /* Config MISO */
    BSP_IO_Configurate(BSP_IO_PORTA_PIN_6, BSP_IO_CONFIG_INPUT_FLOATING | BSP_IO_MODE_INPUT);

    /* Config pin for SPI 2 */
    /* Config NSS */
    BSP_IO_Configurate(BSP_IO_PORTB_PIN_12, BSP_IO_CONFIG_INPUT_FLOATING | BSP_IO_MODE_INPUT);

    /* Config SCK */
    BSP_IO_Configurate(BSP_IO_PORTB_PIN_13, BSP_IO_CONFIG_INPUT_FLOATING | BSP_IO_MODE_INPUT);

    /* Config MOSI */
    BSP_IO_Configurate(BSP_IO_PORTB_PIN_15, BSP_IO_CONFIG_INPUT_FLOATING | BSP_IO_MODE_INPUT);

    /* Config MISO */
    BSP_IO_Configurate(BSP_IO_PORTB_PIN_14, BSP_IO_CONFIG_OUTPUT_ALTER_PUSH_PULL | BSP_IO_MODE_OUTPUT_50MHZ | BSP_IO_OUTPUT_INIT_STATE_HIGH);
}

static void spi_test_set_up_spi2_master_spi1_slave(void)
{
    /* Config pin for SPI 2 */
    /* Config NSS */
    BSP_IO_Configurate(BSP_IO_PORTB_PIN_12, BSP_IO_CONFIG_OUTPUT_GPIO_PUSH_PULL | BSP_IO_MODE_OUTPUT_50MHZ | BSP_IO_OUTPUT_INIT_STATE_HIGH);

    /* Config SCK */
    BSP_IO_Configurate(BSP_IO_PORTB_PIN_13, BSP_IO_CONFIG_OUTPUT_ALTER_PUSH_PULL | BSP_IO_MODE_OUTPUT_50MHZ | BSP_IO_OUTPUT_INIT_STATE_HIGH);

    /* Config MOSI */
    BSP_IO_Configurate(BSP_IO_PORTB_PIN_15, BSP_IO_CONFIG_OUTPUT_ALTER_PUSH_PULL | BSP_IO_MODE_OUTPUT_50MHZ | BSP_IO_OUTPUT_INIT_STATE_HIGH);

    /* Config MISO */
    BSP_IO_Configurate(BSP_IO_PORTB_PIN_14, BSP_IO_CONFIG_INPUT_FLOATING | BSP_IO_MODE_INPUT);

    /* Config pin for SPI 1 */
    /* Config NSS */
    BSP_IO_Configurate(BSP_IO_PORTA_PIN_4, BSP_IO_CONFIG_INPUT_FLOATING | BSP_IO_MODE_INPUT);

    /* Config SCK */
    BSP_IO_Configurate(BSP_IO_PORTA_PIN_5, BSP_IO_CONFIG_INPUT_FLOATING | BSP_IO_MODE_INPUT);

    /* Config MOSI */
    BSP_IO_Configurate(BSP_IO_PORTA_PIN_7, BSP_IO_CONFIG_INPUT_FLOATING | BSP_IO_MODE_INPUT);

    /* Config MISO */
    BSP_IO_Configurate(BSP_IO_PORTA_PIN_6, BSP_IO_CONFIG_OUTPUT_ALTER_PUSH_PULL | BSP_IO_MODE_OUTPUT_50MHZ | BSP_IO_OUTPUT_INIT_STATE_HIGH);
}

#define SPI_TEST_SIZE 1024U

spi_ctrl_t spi_ctrl_1;
spi_cfg_t spi_cfg_1 = 
{
    .configuration_b = 
    {
        .baud_rate = SPI_BAUD_RATE_CLK_DIV_2,
        .crc_en = SPI_HARDWARE_CRC_DISABLE,
        .data_frame = SPI_DATA_FRAME_FORMAT_8_BITS,
        .data_mode = SPI_DATA_MODE_0,
        .frame_format = SPI_FRAME_FORMAT_MSB_FIRST,
        .mode = SPI_MODE_MASTER,
        .slave_select_mode = SPI_SLAVE_SELECT_MANUAL,
        .soft_slave_en = SPI_SOFTWARE_SLAVE_MANAGE_ENABLE,
        .dma_transmit_en = 0U,
        .dma_receive_en = 0U
    },
    .direction = SPI_DIRECTION_2_LINES_FULL_DUPLEX,
    .err_ipl = BSP_IRQ_DISABLE,
    .transmit_ipl = BSP_IRQ_DISABLE,
    .receive_ipl = BSP_IRQ_DISABLE,
    .p_dma_rx_cfg = NULL,
    .p_dma_rx_ctrl = NULL,
    .p_dma_tx_cfg = NULL,
    .p_dma_tx_ctrl = NULL,
    .unit = SPI_UNIT_1
};

spi_ctrl_t spi_ctrl_2;
spi_cfg_t spi_cfg_2 = 
{
    .configuration_b = 
    {
        .baud_rate = SPI_BAUD_RATE_CLK_DIV_2,
        .crc_en = SPI_HARDWARE_CRC_DISABLE,
        .data_frame = SPI_DATA_FRAME_FORMAT_8_BITS,
        .data_mode = SPI_DATA_MODE_0,
        .frame_format = SPI_FRAME_FORMAT_MSB_FIRST,
        .mode = SPI_MODE_SLAVE,
        .slave_select_mode = SPI_SLAVE_SELECT_MANUAL,
        .soft_slave_en = SPI_SOFTWARE_SLAVE_MANAGE_ENABLE,
        .dma_transmit_en = 0U,
        .dma_receive_en = 0U
    },
    .direction = SPI_DIRECTION_2_LINES_FULL_DUPLEX,
    .err_ipl = BSP_IRQ_DISABLE,
    .transmit_ipl = BSP_IRQ_DISABLE,
    .receive_ipl = BSP_IRQ_DISABLE,
    .p_dma_rx_cfg = NULL,
    .p_dma_rx_ctrl = NULL,
    .p_dma_tx_cfg = NULL,
    .p_dma_tx_ctrl = NULL,
    .unit = SPI_UNIT_2
};

static uint8_t src[SPI_TEST_SIZE];
static uint8_t dest[SPI_TEST_SIZE];

void spi_polling_test_case(void)
{
    uint16_t dummy_value;
    /* Test case 1: Test transmit - receive for SPI1 master and SPI2 slave with polling */

    /* Set up pin */
    spi_test_set_up_spi1_master_spi2_slave();

    for(uint16_t i = 0U; i < SPI_TEST_SIZE; i++)
    {
        src[i] = (i % 26U) + 'A';
    }
    for(uint16_t i = 0U; i < SPI_TEST_SIZE; i++)
    {
        dest[i] = 0U;
    }

    /* Open master first */
    SPI_Open(&spi_ctrl_1, &spi_cfg_1);
    SPI_Open(&spi_ctrl_2, &spi_cfg_2);
    BSP_IO_Write(BSP_IO_PORTA_PIN_4, BSP_IO_STATE_LOW);

    for(uint16_t i = 0U; i < SPI_TEST_SIZE; i++)
    {
        /* Master transmit */
        SPI_PollingWrite(&spi_ctrl_1, &src[i]);
        
        /* Slave receive */
        SPI_PollingRead(&spi_ctrl_2, &dest[i]);
    }

    /* Since it's a full-duplex mode, slave also sent the data to master. 
       Perform dummy read to clear RXNE flag */
    SPI_PollingRead(&spi_ctrl_1, &dummy_value);

    BSP_IO_Write(BSP_IO_PORTA_PIN_4, BSP_IO_STATE_HIGH);

    /* Check transmit-receive data */
    for(uint16_t i = 0U; i < SPI_TEST_SIZE; i++)
    {
        ASSERT(src[i] == dest[i]);
    }

    /* Check error flags */
    ASSERT(spi_ctrl_1.p_reg->SPI_SR_b.BSY == 0U);
    ASSERT(spi_ctrl_1.p_reg->SPI_SR_b.OVR == 0U);
    ASSERT(spi_ctrl_1.p_reg->SPI_SR_b.UDR == 0U);
    ASSERT(spi_ctrl_2.p_reg->SPI_SR_b.BSY == 0U);
    ASSERT(spi_ctrl_2.p_reg->SPI_SR_b.OVR == 0U);
    ASSERT(spi_ctrl_2.p_reg->SPI_SR_b.UDR == 0U);

    /* Open slave first */
    SPI_Close(&spi_ctrl_2);
    SPI_Close(&spi_ctrl_1);

    for(uint16_t i = 0U; i < SPI_TEST_SIZE; i++)
    {
        src[i] = (i % 26U) + 'A';
    }
    for(uint16_t i = 0U; i < SPI_TEST_SIZE; i++)
    {
        dest[i] = 0U;
    }
    
    /* Test case 2: Test transmit - receive for SPI2 master and SPI1 slave with polling */
    /* Set up pin */
    spi_test_set_up_spi2_master_spi1_slave();

    for(uint16_t i = 0U; i < SPI_TEST_SIZE; i++)
    {
        src[i] = (i % 26U) + 'A';
    }
    for(uint16_t i = 0U; i < SPI_TEST_SIZE; i++)
    {
        dest[i] = 0U;
    }

    spi_cfg_1.configuration_b.mode = SPI_MODE_SLAVE;
    spi_cfg_2.configuration_b.mode = SPI_MODE_MASTER;

    /* Open master first */
    SPI_Open(&spi_ctrl_2, &spi_cfg_2);
    SPI_Open(&spi_ctrl_1, &spi_cfg_1);
    BSP_IO_Write(BSP_IO_PORTB_PIN_12, BSP_IO_STATE_LOW);

    for(uint16_t i = 0U; i < SPI_TEST_SIZE; i++)
    {
        /* Master transmit */
        SPI_PollingWrite(&spi_ctrl_2, &src[i]);
        
        /* Slave receive */
        SPI_PollingRead(&spi_ctrl_1, &dest[i]);
    }

    /* Since it's a full-duplex mode, slave also sent the data to master. 
       Perform dummy read to clear RXNE flag */
    SPI_PollingRead(&spi_ctrl_2, &dummy_value);

    BSP_IO_Write(BSP_IO_PORTB_PIN_12, BSP_IO_STATE_HIGH);

    /* Check transmit-receive data */
    for(uint16_t i = 0U; i < SPI_TEST_SIZE; i++)
    {
        ASSERT(src[i] == dest[i]);
    }

    /* Check error flags */
    ASSERT(spi_ctrl_1.p_reg->SPI_SR_b.BSY == 0U);
    ASSERT(spi_ctrl_1.p_reg->SPI_SR_b.OVR == 0U);
    ASSERT(spi_ctrl_1.p_reg->SPI_SR_b.UDR == 0U);
    ASSERT(spi_ctrl_2.p_reg->SPI_SR_b.BSY == 0U);
    ASSERT(spi_ctrl_2.p_reg->SPI_SR_b.OVR == 0U);
    ASSERT(spi_ctrl_2.p_reg->SPI_SR_b.UDR == 0U);

    /* Close slave first */
    SPI_Close(&spi_ctrl_1);
    SPI_Close(&spi_ctrl_2);
}

spi_ctrl_t spi_ctrl_3;
spi_cfg_t spi_cfg_3 = 
{
    .configuration_b = 
    {
        .baud_rate = SPI_BAUD_RATE_CLK_DIV_2,
        .crc_en = SPI_HARDWARE_CRC_DISABLE,
        .data_frame = SPI_DATA_FRAME_FORMAT_8_BITS,
        .data_mode = SPI_DATA_MODE_0,
        .frame_format = SPI_FRAME_FORMAT_MSB_FIRST,
        .mode = SPI_MODE_MASTER,
        .slave_select_mode = SPI_SLAVE_SELECT_MANUAL,
        .soft_slave_en = SPI_SOFTWARE_SLAVE_MANAGE_ENABLE,
        .dma_transmit_en = 0U,
        .dma_receive_en = 0U
    },
    .direction = SPI_DIRECTION_2_LINES_FULL_DUPLEX,
    .err_ipl = BSP_IRQ_DISABLE,
    .transmit_ipl = 12U,
    .receive_ipl = 11U,
    .p_dma_rx_cfg = NULL,
    .p_dma_rx_ctrl = NULL,
    .p_dma_tx_cfg = NULL,
    .p_dma_tx_ctrl = NULL,
    .unit = SPI_UNIT_1
};

spi_ctrl_t spi_ctrl_4;
spi_cfg_t spi_cfg_4 = 
{
    .configuration_b = 
    {
        .baud_rate = SPI_BAUD_RATE_CLK_DIV_2,
        .crc_en = SPI_HARDWARE_CRC_DISABLE,
        .data_frame = SPI_DATA_FRAME_FORMAT_8_BITS,
        .data_mode = SPI_DATA_MODE_0,
        .frame_format = SPI_FRAME_FORMAT_MSB_FIRST,
        .mode = SPI_MODE_SLAVE,
        .slave_select_mode = SPI_SLAVE_SELECT_MANUAL,
        .soft_slave_en = SPI_SOFTWARE_SLAVE_MANAGE_ENABLE,
        .dma_transmit_en = 0U,
        .dma_receive_en = 0U
    },
    .direction = SPI_DIRECTION_2_LINES_FULL_DUPLEX,
    .err_ipl = BSP_IRQ_DISABLE,
    .transmit_ipl = BSP_IRQ_DISABLE,
    .receive_ipl = 11U,
    .p_dma_rx_cfg = NULL,
    .p_dma_rx_ctrl = NULL,
    .p_dma_tx_cfg = NULL,
    .p_dma_tx_ctrl = NULL,
    .unit = SPI_UNIT_2
};

spi_callback_status_t master_callback_status;
spi_callback_status_t slave_callback_status;

void user_master_callback(void * p_ctrl)
{
    master_callback_status = ((spi_ctrl_t *) p_ctrl)->callback_status;
}

void user_slave_callback(void * p_ctrl)
{
    slave_callback_status = ((spi_ctrl_t *) p_ctrl)->callback_status;
}

void spi_interrupt_test_case(void)
{
    /* Test case 1: SPI1 master - SPI2 slave */
    /* Set up pin */
    spi_test_set_up_spi1_master_spi2_slave();

    for(uint16_t i = 0U; i < SPI_TEST_SIZE; i++)
    {
        src[i] = (i % 26U) + 'A';
    }

    for(uint16_t i = 0U; i < SPI_TEST_SIZE; i++)
    {
        dest[i] = 0U;
    }

    master_callback_status = SPI_CALLBACK_STATUS_NONE;
    slave_callback_status = SPI_CALLBACK_STATUS_NONE;

    /* Open master first */
    SPI_Open(&spi_ctrl_3, &spi_cfg_3);
    spi_cfg_4.transmit_ipl = 12U;
    SPI_Open(&spi_ctrl_4, &spi_cfg_4);
    SPI_CallbackSet(&spi_ctrl_3, user_master_callback);
    SPI_CallbackSet(&spi_ctrl_4, user_slave_callback);

    BSP_IO_Write(BSP_IO_PORTA_PIN_4, BSP_IO_STATE_LOW);

    SPI_Read(&spi_ctrl_4, &dest, SPI_TEST_SIZE);
    SPI_Write(&spi_ctrl_3, &src, SPI_TEST_SIZE);

    while((master_callback_status == SPI_CALLBACK_STATUS_NONE) || (slave_callback_status == SPI_CALLBACK_STATUS_NONE));

    BSP_IO_Write(BSP_IO_PORTA_PIN_4, BSP_IO_STATE_HIGH);

    ASSERT(master_callback_status == SPI_CALLBACK_STATUS_TRANSMIT_COMPLETE);
    ASSERT(slave_callback_status == SPI_CALLBACK_STATUS_RECEIVE_COMPLETE);

    /* Check transmit-receive data */
    for(uint16_t i = 0U; i < SPI_TEST_SIZE; i++)
    {
        ASSERT(src[i] == dest[i]);
    }

    /* Check error flags */
    ASSERT(spi_ctrl_3.p_reg->SPI_SR_b.BSY == 0U);
    ASSERT(spi_ctrl_3.p_reg->SPI_SR_b.OVR == 0U);
    ASSERT(spi_ctrl_3.p_reg->SPI_SR_b.UDR == 0U);
    ASSERT(spi_ctrl_4.p_reg->SPI_SR_b.BSY == 0U);
    ASSERT(spi_ctrl_4.p_reg->SPI_SR_b.OVR == 0U);
    ASSERT(spi_ctrl_4.p_reg->SPI_SR_b.UDR == 0U);

    /* Close slave first */
    SPI_Close(&spi_ctrl_4);
    SPI_Close(&spi_ctrl_3);

    /* Test case 2: CRC feature */
    for(uint16_t i = 0U; i < SPI_TEST_SIZE; i++)
    {
        src[i] = (i % 26U) + 'A';
    }

    for(uint16_t i = 0U; i < SPI_TEST_SIZE; i++)
    {
        dest[i] = 0U;
    }

    master_callback_status = SPI_CALLBACK_STATUS_NONE;
    slave_callback_status = SPI_CALLBACK_STATUS_NONE;

    spi_cfg_3.configuration_b.crc_en = SPI_HARDWARE_CRC_ENABLE;
    spi_cfg_3.direction = SPI_DIRECTION_1_LINE_TRANSMIT_ONLY;
    /* Set baud rate a bit slower to gurantee the CRC work perfectly */
    spi_cfg_3.configuration_b.baud_rate = SPI_BAUD_RATE_CLK_DIV_128;
    spi_cfg_4.configuration_b.crc_en = SPI_HARDWARE_CRC_ENABLE;
    spi_cfg_4.configuration_b.baud_rate = SPI_BAUD_RATE_CLK_DIV_4;
    /* Developer doesn't know why only these 2 baud rate div options can perform CRC smoothly */

    /* Open master first */
    SPI_Open(&spi_ctrl_3, &spi_cfg_3);
    SPI_Open(&spi_ctrl_4, &spi_cfg_4);
    SPI_CallbackSet(&spi_ctrl_3, user_master_callback);
    SPI_CallbackSet(&spi_ctrl_4, user_slave_callback);

    BSP_IO_Write(BSP_IO_PORTA_PIN_4, BSP_IO_STATE_LOW);

    SPI_Read(&spi_ctrl_4, &dest, SPI_TEST_SIZE);
    SPI_Write(&spi_ctrl_3, &src, SPI_TEST_SIZE);

    while((master_callback_status == SPI_CALLBACK_STATUS_NONE) || (slave_callback_status == SPI_CALLBACK_STATUS_NONE));

    BSP_IO_Write(BSP_IO_PORTA_PIN_4, BSP_IO_STATE_HIGH);

    ASSERT(master_callback_status == SPI_CALLBACK_STATUS_TRANSMIT_COMPLETE);
    ASSERT(slave_callback_status == SPI_CALLBACK_STATUS_RECEIVE_COMPLETE);

    /* Check transmit-receive data */
    for(uint16_t i = 0U; i < SPI_TEST_SIZE; i++)
    {
        ASSERT(src[i] == dest[i]);
    }

    /* Check error flags */
    ASSERT(spi_ctrl_3.p_reg->SPI_SR_b.BSY == 0U);
    ASSERT(spi_ctrl_3.p_reg->SPI_SR_b.OVR == 0U);
    ASSERT(spi_ctrl_3.p_reg->SPI_SR_b.UDR == 0U);
    ASSERT(spi_ctrl_3.p_reg->SPI_SR_b.CRCERR == 0U);
    ASSERT(spi_ctrl_4.p_reg->SPI_SR_b.BSY == 0U);
    ASSERT(spi_ctrl_4.p_reg->SPI_SR_b.OVR == 0U);
    ASSERT(spi_ctrl_4.p_reg->SPI_SR_b.UDR == 0U);
    ASSERT(spi_ctrl_4.p_reg->SPI_SR_b.CRCERR == 0U);

    spi_cfg_3.configuration_b.baud_rate = SPI_BAUD_RATE_CLK_DIV_2;
    spi_cfg_4.configuration_b.baud_rate = SPI_BAUD_RATE_CLK_DIV_2;
    spi_cfg_3.direction = SPI_DIRECTION_2_LINES_FULL_DUPLEX;
    /* Close slave first */
    SPI_Close(&spi_ctrl_4);
    SPI_Close(&spi_ctrl_3);

    /* Test case 3: SPI1 slave - SPI2 master */
    /* Set up pin */
    spi_test_set_up_spi2_master_spi1_slave();

    for(uint16_t i = 0U; i < SPI_TEST_SIZE; i++)
    {
        src[i] = (i % 26U) + 'A';
    }

    for(uint16_t i = 0U; i < SPI_TEST_SIZE; i++)
    {
        dest[i] = 0U;
    }

    master_callback_status = SPI_CALLBACK_STATUS_NONE;
    slave_callback_status = SPI_CALLBACK_STATUS_NONE;

    spi_cfg_3.configuration_b.crc_en = SPI_HARDWARE_CRC_DISABLE;
    spi_cfg_4.configuration_b.crc_en = SPI_HARDWARE_CRC_DISABLE;
    spi_cfg_3.configuration_b.mode = SPI_MODE_SLAVE;
    spi_cfg_3.receive_ipl = 11U;
    spi_cfg_3.transmit_ipl = BSP_IRQ_DISABLE;
    spi_cfg_4.configuration_b.mode = SPI_MODE_MASTER;
    spi_cfg_4.receive_ipl = 11U;
    spi_cfg_4.transmit_ipl = 12U;

    /* Open master first */
    SPI_Open(&spi_ctrl_4, &spi_cfg_4);
    SPI_Open(&spi_ctrl_3, &spi_cfg_3);
    SPI_CallbackSet(&spi_ctrl_4, user_master_callback);
    SPI_CallbackSet(&spi_ctrl_3, user_slave_callback);

    BSP_IO_Write(BSP_IO_PORTB_PIN_12, BSP_IO_STATE_LOW);

    SPI_Read(&spi_ctrl_3, &dest, SPI_TEST_SIZE);
    SPI_Write(&spi_ctrl_4, &src, SPI_TEST_SIZE);

    while((master_callback_status == SPI_CALLBACK_STATUS_NONE) || (slave_callback_status == SPI_CALLBACK_STATUS_NONE));

    BSP_IO_Write(BSP_IO_PORTB_PIN_12, BSP_IO_STATE_HIGH);

    ASSERT(master_callback_status == SPI_CALLBACK_STATUS_TRANSMIT_COMPLETE);
    ASSERT(slave_callback_status == SPI_CALLBACK_STATUS_RECEIVE_COMPLETE);

    /* Check transmit-receive data */
    for(uint16_t i = 0U; i < SPI_TEST_SIZE; i++)
    {
        ASSERT(src[i] == dest[i]);
    }

    /* Check error flags */
    ASSERT(spi_ctrl_3.p_reg->SPI_SR_b.BSY == 0U);
    ASSERT(spi_ctrl_3.p_reg->SPI_SR_b.OVR == 0U);
    ASSERT(spi_ctrl_3.p_reg->SPI_SR_b.UDR == 0U);
    ASSERT(spi_ctrl_4.p_reg->SPI_SR_b.BSY == 0U);
    ASSERT(spi_ctrl_4.p_reg->SPI_SR_b.OVR == 0U);
    ASSERT(spi_ctrl_4.p_reg->SPI_SR_b.UDR == 0U);

    /* Close slave first */
    SPI_Close(&spi_ctrl_3);
    SPI_Close(&spi_ctrl_4);
}

void spi_interrupt_test_case_1(void)
{
    /* Test case 1: SPI1 master - SPI2 slave, transmit only - receive only mode */
    /* Set up pin */
    spi_test_set_up_spi1_master_spi2_slave();

    for(uint16_t i = 0U; i < SPI_TEST_SIZE; i++)
    {
        src[i] = (i % 26U) + 'A';
    }

    for(uint16_t i = 0U; i < SPI_TEST_SIZE; i++)
    {
        dest[i] = 0U;
    }

    master_callback_status = SPI_CALLBACK_STATUS_NONE;
    slave_callback_status = SPI_CALLBACK_STATUS_NONE;

    spi_cfg_3.configuration_b.mode = SPI_MODE_MASTER;
    spi_cfg_3.receive_ipl = BSP_IRQ_DISABLE;
    spi_cfg_3.transmit_ipl = 12U;
    spi_cfg_3.direction = SPI_DIRECTION_1_LINE_TRANSMIT_ONLY;
    spi_cfg_4.configuration_b.mode = SPI_MODE_SLAVE;
    spi_cfg_4.receive_ipl = 11U;
    spi_cfg_4.transmit_ipl = BSP_IRQ_DISABLE;
    spi_cfg_4.direction = SPI_DIRECTION_2_LINES_RECEIVE_ONLY;
    
    /* Open master first */
    SPI_Open(&spi_ctrl_3, &spi_cfg_3);
    SPI_Open(&spi_ctrl_4, &spi_cfg_4);
    SPI_CallbackSet(&spi_ctrl_3, user_master_callback);
    SPI_CallbackSet(&spi_ctrl_4, user_slave_callback);

    BSP_IO_Write(BSP_IO_PORTA_PIN_4, BSP_IO_STATE_LOW);

    SPI_Read(&spi_ctrl_4, &dest, SPI_TEST_SIZE);
    SPI_Write(&spi_ctrl_3, &src, SPI_TEST_SIZE);

    while((master_callback_status == SPI_CALLBACK_STATUS_NONE) || (slave_callback_status == SPI_CALLBACK_STATUS_NONE));

    BSP_IO_Write(BSP_IO_PORTA_PIN_4, BSP_IO_STATE_HIGH);

    ASSERT(master_callback_status == SPI_CALLBACK_STATUS_TRANSMIT_COMPLETE);
    ASSERT(slave_callback_status == SPI_CALLBACK_STATUS_RECEIVE_COMPLETE);

    /* Check transmit-receive data */
    for(uint16_t i = 0U; i < SPI_TEST_SIZE; i++)
    {
        ASSERT(src[i] == dest[i]);
    }

    /* Check error flags */
    ASSERT(spi_ctrl_3.p_reg->SPI_SR_b.BSY == 0U);
    ASSERT(spi_ctrl_3.p_reg->SPI_SR_b.OVR == 0U);
    ASSERT(spi_ctrl_3.p_reg->SPI_SR_b.UDR == 0U);
    ASSERT(spi_ctrl_4.p_reg->SPI_SR_b.BSY == 0U);
    ASSERT(spi_ctrl_4.p_reg->SPI_SR_b.OVR == 0U);
    ASSERT(spi_ctrl_4.p_reg->SPI_SR_b.UDR == 0U);

    /* Close slave first */
    SPI_Close(&spi_ctrl_4);
    SPI_Close(&spi_ctrl_3);

    /* Test case 2: SPI1 slave - SPI2 master, transmit only - receive only mode */
    /* Set up pin */
    spi_test_set_up_spi2_master_spi1_slave();

    for(uint16_t i = 0U; i < SPI_TEST_SIZE; i++)
    {
        src[i] = (i % 26U) + 'A';
    }

    for(uint16_t i = 0U; i < SPI_TEST_SIZE; i++)
    {
        dest[i] = 0U;
    }

    master_callback_status = SPI_CALLBACK_STATUS_NONE;
    slave_callback_status = SPI_CALLBACK_STATUS_NONE;

    spi_cfg_3.configuration_b.mode = SPI_MODE_SLAVE;
    spi_cfg_3.receive_ipl = 11U;
    spi_cfg_3.transmit_ipl = BSP_IRQ_DISABLE;
    spi_cfg_3.direction = SPI_DIRECTION_2_LINES_RECEIVE_ONLY;
    spi_cfg_4.configuration_b.mode = SPI_MODE_MASTER;
    spi_cfg_4.receive_ipl = BSP_IRQ_DISABLE;
    spi_cfg_4.transmit_ipl = 12U;
    spi_cfg_4.direction = SPI_DIRECTION_1_LINE_TRANSMIT_ONLY;
    
    /* Open master first */
    SPI_Open(&spi_ctrl_4, &spi_cfg_4);
    SPI_Open(&spi_ctrl_3, &spi_cfg_3);
    SPI_CallbackSet(&spi_ctrl_4, user_master_callback);
    SPI_CallbackSet(&spi_ctrl_3, user_slave_callback);

    BSP_IO_Write(BSP_IO_PORTB_PIN_12, BSP_IO_STATE_LOW);

    SPI_Read(&spi_ctrl_3, &dest, SPI_TEST_SIZE);
    SPI_Write(&spi_ctrl_4, &src, SPI_TEST_SIZE);

    while((master_callback_status == SPI_CALLBACK_STATUS_NONE) || (slave_callback_status == SPI_CALLBACK_STATUS_NONE));

    BSP_IO_Write(BSP_IO_PORTB_PIN_12, BSP_IO_STATE_HIGH);

    ASSERT(master_callback_status == SPI_CALLBACK_STATUS_TRANSMIT_COMPLETE);
    ASSERT(slave_callback_status == SPI_CALLBACK_STATUS_RECEIVE_COMPLETE);

    /* Check transmit-receive data */
    for(uint16_t i = 0U; i < SPI_TEST_SIZE; i++)
    {
        ASSERT(src[i] == dest[i]);
    }

    /* Check error flags */
    ASSERT(spi_ctrl_3.p_reg->SPI_SR_b.BSY == 0U);
    ASSERT(spi_ctrl_3.p_reg->SPI_SR_b.OVR == 0U);
    ASSERT(spi_ctrl_3.p_reg->SPI_SR_b.UDR == 0U);
    ASSERT(spi_ctrl_4.p_reg->SPI_SR_b.BSY == 0U);
    ASSERT(spi_ctrl_4.p_reg->SPI_SR_b.OVR == 0U);
    ASSERT(spi_ctrl_4.p_reg->SPI_SR_b.UDR == 0U);

    /* Close slave first */
    SPI_Close(&spi_ctrl_3);
    SPI_Close(&spi_ctrl_4);
}

void spi_error_test_case(void)
{
    /* Test case 1: Overrun error interrupt */
    spi_test_set_up_spi1_master_spi2_slave();

    master_callback_status = SPI_CALLBACK_STATUS_NONE;
    slave_callback_status = SPI_CALLBACK_STATUS_NONE;

    spi_cfg_3.configuration_b.mode = SPI_MODE_MASTER;
    spi_cfg_3.receive_ipl = 11U;
    spi_cfg_3.transmit_ipl = 12U;
    spi_cfg_3.direction = SPI_DIRECTION_2_LINES_FULL_DUPLEX;
    spi_cfg_4.configuration_b.mode = SPI_MODE_SLAVE;
    spi_cfg_4.receive_ipl = BSP_IRQ_DISABLE;
    spi_cfg_4.transmit_ipl = BSP_IRQ_DISABLE;
    spi_cfg_4.err_ipl = 11U;
    spi_cfg_4.direction = SPI_DIRECTION_2_LINES_FULL_DUPLEX;
    
    /* Open master first */
    SPI_Open(&spi_ctrl_3, &spi_cfg_3);
    SPI_Open(&spi_ctrl_4, &spi_cfg_4);
    SPI_CallbackSet(&spi_ctrl_3, user_master_callback);
    SPI_CallbackSet(&spi_ctrl_4, user_slave_callback);

    BSP_IO_Write(BSP_IO_PORTA_PIN_4, BSP_IO_STATE_LOW);

    SPI_Write(&spi_ctrl_3, &src, 2U);

    while((master_callback_status == SPI_CALLBACK_STATUS_NONE) || (slave_callback_status == SPI_CALLBACK_STATUS_NONE));

    BSP_IO_Write(BSP_IO_PORTA_PIN_4, BSP_IO_STATE_HIGH);

    ASSERT(master_callback_status == SPI_CALLBACK_STATUS_TRANSMIT_COMPLETE);
    ASSERT(slave_callback_status == SPI_CALLBACK_STATUS_OVERRUN);

    /* Check error flags */
    ASSERT(spi_ctrl_3.p_reg->SPI_SR_b.BSY == 0U);
    ASSERT(spi_ctrl_3.p_reg->SPI_SR_b.OVR == 0U);
    ASSERT(spi_ctrl_3.p_reg->SPI_SR_b.UDR == 0U);
    ASSERT(spi_ctrl_3.p_reg->SPI_SR_b.MODF == 0U);
    ASSERT(spi_ctrl_3.p_reg->SPI_SR_b.CRCERR == 0U);
    ASSERT(spi_ctrl_4.p_reg->SPI_SR_b.BSY == 0U);
    ASSERT(spi_ctrl_4.p_reg->SPI_SR_b.OVR == 0U);
    ASSERT(spi_ctrl_4.p_reg->SPI_SR_b.UDR == 0U);
    ASSERT(spi_ctrl_4.p_reg->SPI_SR_b.MODF == 0U);
    ASSERT(spi_ctrl_4.p_reg->SPI_SR_b.CRCERR == 0U);

    /* Close slave first */
    SPI_Close(&spi_ctrl_4);
    SPI_Close(&spi_ctrl_3);

    /* Test case 2: CRC error interrupt */
    master_callback_status = SPI_CALLBACK_STATUS_NONE;
    slave_callback_status = SPI_CALLBACK_STATUS_NONE;

    spi_cfg_3.configuration_b.mode = SPI_MODE_MASTER;
    spi_cfg_3.receive_ipl = BSP_IRQ_DISABLE;
    spi_cfg_3.transmit_ipl = BSP_IRQ_DISABLE;
    spi_cfg_3.err_ipl = 12U;
    spi_cfg_3.configuration_b.crc_en = SPI_HARDWARE_CRC_ENABLE;
    spi_cfg_3.direction = SPI_DIRECTION_1_LINE_TRANSMIT_ONLY;
    spi_cfg_4.configuration_b.mode = SPI_MODE_SLAVE;
    spi_cfg_4.receive_ipl = BSP_IRQ_DISABLE;
    spi_cfg_4.transmit_ipl = BSP_IRQ_DISABLE;
    spi_cfg_4.err_ipl = BSP_IRQ_DISABLE;
    
    /* Open master first */
    SPI_Open(&spi_ctrl_3, &spi_cfg_3);
    SPI_CallbackSet(&spi_ctrl_3, user_master_callback);

    BSP_IO_Write(BSP_IO_PORTA_PIN_4, BSP_IO_STATE_LOW);

    /* Master transmit */
    SPI_PollingWrite(&spi_ctrl_3, &src[0]);
    spi_ctrl_3.p_reg->SPI_CR1_b.CRCNEXT = 1U;

    while((master_callback_status == SPI_CALLBACK_STATUS_NONE));

    BSP_IO_Write(BSP_IO_PORTA_PIN_4, BSP_IO_STATE_HIGH);

    ASSERT(master_callback_status == SPI_CALLBACK_STATUS_CRC_ERROR);

    /* Check error flags */
    ASSERT(spi_ctrl_3.p_reg->SPI_SR_b.BSY == 0U);
    ASSERT(spi_ctrl_3.p_reg->SPI_SR_b.OVR == 0U);
    ASSERT(spi_ctrl_3.p_reg->SPI_SR_b.MODF == 0U);
    ASSERT(spi_ctrl_3.p_reg->SPI_SR_b.CRCERR == 0U);

    SPI_Close(&spi_ctrl_3);

    /* Test case 3: Mode fault error interrupt */
    master_callback_status = SPI_CALLBACK_STATUS_NONE;
    slave_callback_status = SPI_CALLBACK_STATUS_NONE;
    
    /* Open master first */
    SPI_Open(&spi_ctrl_3, &spi_cfg_3);
    SPI_CallbackSet(&spi_ctrl_3, user_master_callback);

    spi_ctrl_3.p_reg->SPI_CR1_b.SSI = 0U;

    while((master_callback_status == SPI_CALLBACK_STATUS_NONE));

    ASSERT(master_callback_status == SPI_CALLBACK_STATUS_MASTER_MODE_FAULT);

    /* Check error flags */
    ASSERT(spi_ctrl_3.p_reg->SPI_SR_b.BSY == 0U);
    ASSERT(spi_ctrl_3.p_reg->SPI_SR_b.OVR == 0U);
    ASSERT(spi_ctrl_3.p_reg->SPI_SR_b.UDR == 0U);
    ASSERT(spi_ctrl_3.p_reg->SPI_SR_b.MODF == 0U);
    ASSERT(spi_ctrl_3.p_reg->SPI_SR_b.CRCERR == 0U);

    SPI_Close(&spi_ctrl_3);
}

dma_ctrl_t dma_spi_tx_ctrl;
dma_cfg_t dma_spi_tx_cfg = 
{
    .configuration_b = 
    {
        .tranfer_direction = DMA_TRANFER_DIRECTION_READ_FROM_MEM,
        .circular_mode = DMA_CIRCULAR_MODE_DISABLE,
        .m2m_mode = DMA_MEM2MEM_MODE_DISABLE,
        .mem_inc_mode = DMA_MEM_INC_MODE_ENABLE,
        .periph_inc_mode = DMA_PERIPH_INC_MODE_DISABLE,
        .mem_size = DMA_MEM_SIZE_8_BITS,
        .periph_size = DMA_PERIPH_SIZE_8_BITS,
        .channel_priority = DMA_CHANNEL_PRIORITY_LOW
    },
    .tranfer_ipl = BSP_IRQ_DISABLE,
    .half_tranfer_ipl = BSP_IRQ_DISABLE,
    .err_ipl = BSP_IRQ_DISABLE,
    .channel = 3U,
    .unit = DMA_UNIT_1
};

dma_ctrl_t dma_spi_rx_ctrl;
dma_cfg_t dma_spi_rx_cfg = 
{
    .configuration_b = 
    {
        .tranfer_direction = DMA_TRANFER_DIRECTION_READ_FROM_PERIPH,
        .circular_mode = DMA_CIRCULAR_MODE_DISABLE,
        .m2m_mode = DMA_MEM2MEM_MODE_DISABLE,
        .mem_inc_mode = DMA_MEM_INC_MODE_ENABLE,
        .periph_inc_mode = DMA_PERIPH_INC_MODE_DISABLE,
        .mem_size = DMA_MEM_SIZE_8_BITS,
        .periph_size = DMA_PERIPH_SIZE_8_BITS,
        .channel_priority = DMA_CHANNEL_PRIORITY_HIGH
    },
    .tranfer_ipl = BSP_IRQ_DISABLE,
    .half_tranfer_ipl = BSP_IRQ_DISABLE,
    .err_ipl = BSP_IRQ_DISABLE,
    .channel = 4U,
    .unit = DMA_UNIT_1
};

spi_ctrl_t spi_ctrl_dma_0;
spi_cfg_t spi_cfg_dma_0 = 
{
    .configuration_b = 
    {
        .baud_rate = SPI_BAUD_RATE_CLK_DIV_4,
        .crc_en = SPI_HARDWARE_CRC_DISABLE,
        .data_frame = SPI_DATA_FRAME_FORMAT_8_BITS,
        .data_mode = SPI_DATA_MODE_0,
        .frame_format = SPI_FRAME_FORMAT_MSB_FIRST,
        .mode = SPI_MODE_MASTER,
        .slave_select_mode = SPI_SLAVE_SELECT_MANUAL,
        .soft_slave_en = SPI_SOFTWARE_SLAVE_MANAGE_ENABLE,
        .dma_transmit_en = 1U,
        .dma_receive_en = 1U
    },
    .direction = SPI_DIRECTION_2_LINES_FULL_DUPLEX,
    .err_ipl = BSP_IRQ_DISABLE,
    .transmit_ipl = BSP_IRQ_DISABLE,
    .receive_ipl = BSP_IRQ_DISABLE,
    .p_dma_rx_cfg = NULL,
    .p_dma_rx_ctrl = NULL,
    .p_dma_tx_cfg = &dma_spi_tx_cfg,
    .p_dma_tx_ctrl = &dma_spi_tx_ctrl,
    .unit = SPI_UNIT_1
};

spi_ctrl_t spi_ctrl_dma_1;
spi_cfg_t spi_cfg_dma_1 = 
{
    .configuration_b = 
    {
        .baud_rate = SPI_BAUD_RATE_CLK_DIV_4,
        .crc_en = SPI_HARDWARE_CRC_DISABLE,
        .data_frame = SPI_DATA_FRAME_FORMAT_8_BITS,
        .data_mode = SPI_DATA_MODE_0,
        .frame_format = SPI_FRAME_FORMAT_MSB_FIRST,
        .mode = SPI_MODE_SLAVE,
        .slave_select_mode = SPI_SLAVE_SELECT_MANUAL,
        .soft_slave_en = SPI_SOFTWARE_SLAVE_MANAGE_ENABLE,
        .dma_transmit_en = 0U,
        .dma_receive_en = 1U
    },
    .direction = SPI_DIRECTION_2_LINES_FULL_DUPLEX,
    .err_ipl = BSP_IRQ_DISABLE,
    .transmit_ipl = BSP_IRQ_DISABLE,
    .receive_ipl = BSP_IRQ_DISABLE,
    .p_dma_rx_cfg = &dma_spi_rx_cfg,
    .p_dma_rx_ctrl = &dma_spi_rx_ctrl,
    .p_dma_tx_cfg = NULL,
    .p_dma_tx_ctrl = NULL,
    .unit = SPI_UNIT_2
};

void spi_dma_test_case(void)
{
    uint8_t dummy_value;
    /* Test case 1: SPI1 master - SPI2 slave */
    /* Set up pin */
    spi_test_set_up_spi1_master_spi2_slave();

    for(uint16_t i = 0U; i < SPI_TEST_SIZE; i++)
    {
        src[i] = (i % 26U) + 'A';
    }

    for(uint16_t i = 0U; i < SPI_TEST_SIZE; i++)
    {
        dest[i] = 0U;
    }

    /* Open master first */
    dma_spi_tx_cfg.channel = 3U;
    dma_spi_rx_cfg.channel = 4U;

    SPI_Open(&spi_ctrl_dma_0, &spi_cfg_dma_0);
    SPI_Open(&spi_ctrl_dma_1, &spi_cfg_dma_1);

    BSP_IO_Write(BSP_IO_PORTA_PIN_4, BSP_IO_STATE_LOW);

    SPI_Read(&spi_ctrl_dma_1, &dest, SPI_TEST_SIZE);
    SPI_Write(&spi_ctrl_dma_0, &src, SPI_TEST_SIZE);

    // Wait for Master DMA to finish TX
    while(spi_ctrl_dma_0.p_reg->SPI_SR_b.BSY); 
    // Wait for Slave DMA to finish RX
    while(spi_ctrl_dma_1.p_reg->SPI_SR_b.BSY);

    /* Dummy read to advoid OVERRUN when transmitting the last data */
    dummy_value = spi_ctrl_dma_0.p_reg->SPI_DR;
    (void) dummy_value;

    BSP_IO_Write(BSP_IO_PORTA_PIN_4, BSP_IO_STATE_HIGH);

    /* Check transmit-receive data */
    for(uint16_t i = 0U; i < SPI_TEST_SIZE; i++)
    {
        ASSERT(src[i] == dest[i]);
    }

    /* Check error flags */
    ASSERT(spi_ctrl_dma_0.p_reg->SPI_SR_b.BSY == 0U);
    ASSERT(spi_ctrl_dma_0.p_reg->SPI_SR_b.OVR == 0U);
    ASSERT(spi_ctrl_dma_0.p_reg->SPI_SR_b.UDR == 0U);
    ASSERT(spi_ctrl_dma_1.p_reg->SPI_SR_b.BSY == 0U);
    ASSERT(spi_ctrl_dma_1.p_reg->SPI_SR_b.OVR == 0U);
    ASSERT(spi_ctrl_dma_1.p_reg->SPI_SR_b.UDR == 0U);

    /* Close slave first */
    SPI_Close(&spi_ctrl_dma_1);
    SPI_Close(&spi_ctrl_dma_0);

    /* Test case 2: SPI2 master - SPI1 slave */
    /* Set up pin */
    spi_test_set_up_spi2_master_spi1_slave();

    for(uint16_t i = 0U; i < SPI_TEST_SIZE; i++)
    {
        src[i] = (i % 26U) + 'A';
    }

    for(uint16_t i = 0U; i < SPI_TEST_SIZE; i++)
    {
        dest[i] = 0U;
    }

    dma_spi_tx_cfg.channel = 5U;
    dma_spi_rx_cfg.channel = 2U;

    spi_cfg_dma_0.configuration_b.dma_transmit_en = 0U;
    spi_cfg_dma_0.configuration_b.dma_receive_en = 1U;
    spi_cfg_dma_0.p_dma_rx_cfg = &dma_spi_rx_cfg;
    spi_cfg_dma_0.p_dma_rx_ctrl = &dma_spi_rx_ctrl;
    spi_cfg_dma_0.configuration_b.mode = SPI_MODE_SLAVE;

    spi_cfg_dma_1.configuration_b.dma_transmit_en = 1U;
    spi_cfg_dma_1.configuration_b.dma_receive_en = 0U;
    spi_cfg_dma_1.p_dma_tx_cfg = &dma_spi_tx_cfg;
    spi_cfg_dma_1.p_dma_tx_ctrl = &dma_spi_tx_ctrl;
    spi_cfg_dma_1.configuration_b.mode = SPI_MODE_MASTER;

    /* Open master first */
    SPI_Open(&spi_ctrl_dma_1, &spi_cfg_dma_1);
    SPI_Open(&spi_ctrl_dma_0, &spi_cfg_dma_0);

    BSP_IO_Write(BSP_IO_PORTB_PIN_12, BSP_IO_STATE_LOW);

    SPI_Read(&spi_ctrl_dma_0, &dest, SPI_TEST_SIZE);
    SPI_Write(&spi_ctrl_dma_1, &src, SPI_TEST_SIZE);

    // Wait for Master DMA to finish TX
    while(spi_ctrl_dma_1.p_reg->SPI_SR_b.BSY);

    // Wait for Slave DMA to finish RX
    while(spi_ctrl_dma_0.p_reg->SPI_SR_b.BSY);

    /* Dummy read to advoid OVERRUN when transmitting the last data */
    dummy_value = spi_ctrl_dma_1.p_reg->SPI_DR;
    (void) dummy_value;

    BSP_IO_Write(BSP_IO_PORTB_PIN_12, BSP_IO_STATE_HIGH);

    /* Check transmit-receive data */
    for(uint16_t i = 0U; i < SPI_TEST_SIZE; i++)
    {
        ASSERT(src[i] == dest[i]);
    }

    /* Check error flags */
    ASSERT(spi_ctrl_dma_0.p_reg->SPI_SR_b.BSY == 0U);
    ASSERT(spi_ctrl_dma_0.p_reg->SPI_SR_b.OVR == 0U);
    ASSERT(spi_ctrl_dma_0.p_reg->SPI_SR_b.UDR == 0U);
    ASSERT(spi_ctrl_dma_1.p_reg->SPI_SR_b.BSY == 0U);
    ASSERT(spi_ctrl_dma_1.p_reg->SPI_SR_b.OVR == 0U);
    ASSERT(spi_ctrl_dma_1.p_reg->SPI_SR_b.UDR == 0U);

    /* Close slave first */
    SPI_Close(&spi_ctrl_dma_0);
    SPI_Close(&spi_ctrl_dma_1);
}

static void spi_set_up_test(void)
{
    spi_cfg_1.configuration_b.baud_rate = SPI_BAUD_RATE_CLK_DIV_2;
    spi_cfg_1.configuration_b.crc_en = SPI_HARDWARE_CRC_DISABLE;
    spi_cfg_1.configuration_b.data_frame = SPI_DATA_FRAME_FORMAT_8_BITS;
    spi_cfg_1.configuration_b.data_mode = SPI_DATA_MODE_0;
    spi_cfg_1.configuration_b.frame_format = SPI_FRAME_FORMAT_MSB_FIRST;
    spi_cfg_1.configuration_b.mode = SPI_MODE_MASTER;
    spi_cfg_1.configuration_b.slave_select_mode = SPI_SLAVE_SELECT_MANUAL;
    spi_cfg_1.configuration_b.soft_slave_en = SPI_SOFTWARE_SLAVE_MANAGE_ENABLE;
    spi_cfg_1.configuration_b.dma_transmit_en = 0U;
    spi_cfg_1.configuration_b.dma_receive_en = 0U;
    spi_cfg_1.direction = SPI_DIRECTION_2_LINES_FULL_DUPLEX;
    spi_cfg_1.err_ipl = BSP_IRQ_DISABLE;
    spi_cfg_1.transmit_ipl = BSP_IRQ_DISABLE;
    spi_cfg_1.receive_ipl = BSP_IRQ_DISABLE;
    spi_cfg_1.p_dma_rx_cfg = NULL;
    spi_cfg_1.p_dma_rx_ctrl = NULL;
    spi_cfg_1.p_dma_tx_cfg = NULL;
    spi_cfg_1.p_dma_tx_ctrl = NULL;
    spi_cfg_1.unit = SPI_UNIT_1;

    spi_cfg_2.configuration_b.baud_rate = SPI_BAUD_RATE_CLK_DIV_2;
    spi_cfg_2.configuration_b.crc_en = SPI_HARDWARE_CRC_DISABLE;
    spi_cfg_2.configuration_b.data_frame = SPI_DATA_FRAME_FORMAT_8_BITS;
    spi_cfg_2.configuration_b.data_mode = SPI_DATA_MODE_0;
    spi_cfg_2.configuration_b.frame_format = SPI_FRAME_FORMAT_MSB_FIRST;
    spi_cfg_2.configuration_b.mode = SPI_MODE_SLAVE;
    spi_cfg_2.configuration_b.slave_select_mode = SPI_SLAVE_SELECT_MANUAL;
    spi_cfg_2.configuration_b.soft_slave_en = SPI_SOFTWARE_SLAVE_MANAGE_ENABLE;
    spi_cfg_2.configuration_b.dma_transmit_en = 0U;
    spi_cfg_2.configuration_b.dma_receive_en = 0U;
    spi_cfg_2.direction = SPI_DIRECTION_2_LINES_FULL_DUPLEX;
    spi_cfg_2.err_ipl = BSP_IRQ_DISABLE;
    spi_cfg_2.transmit_ipl = BSP_IRQ_DISABLE;
    spi_cfg_2.receive_ipl = BSP_IRQ_DISABLE;
    spi_cfg_2.p_dma_rx_cfg = NULL;
    spi_cfg_2.p_dma_rx_ctrl = NULL;
    spi_cfg_2.p_dma_tx_cfg = NULL;
    spi_cfg_2.p_dma_tx_ctrl = NULL;
    spi_cfg_2.unit = SPI_UNIT_2;

    spi_cfg_3.configuration_b.baud_rate = SPI_BAUD_RATE_CLK_DIV_2;
    spi_cfg_3.configuration_b.crc_en = SPI_HARDWARE_CRC_DISABLE;
    spi_cfg_3.configuration_b.data_frame = SPI_DATA_FRAME_FORMAT_8_BITS;
    spi_cfg_3.configuration_b.data_mode = SPI_DATA_MODE_0;
    spi_cfg_3.configuration_b.frame_format = SPI_FRAME_FORMAT_MSB_FIRST;
    spi_cfg_3.configuration_b.mode = SPI_MODE_MASTER;
    spi_cfg_3.configuration_b.slave_select_mode = SPI_SLAVE_SELECT_MANUAL;
    spi_cfg_3.configuration_b.soft_slave_en = SPI_SOFTWARE_SLAVE_MANAGE_ENABLE;
    spi_cfg_3.configuration_b.dma_transmit_en = 0U;
    spi_cfg_3.configuration_b.dma_receive_en = 0U;
    spi_cfg_3.direction = SPI_DIRECTION_2_LINES_FULL_DUPLEX;
    spi_cfg_3.err_ipl = BSP_IRQ_DISABLE;
    spi_cfg_3.transmit_ipl = 12U;
    spi_cfg_3.receive_ipl = 11U;
    spi_cfg_3.p_dma_rx_cfg = NULL;
    spi_cfg_3.p_dma_rx_ctrl = NULL;
    spi_cfg_3.p_dma_tx_cfg = NULL;
    spi_cfg_3.p_dma_tx_ctrl = NULL;
    spi_cfg_3.unit = SPI_UNIT_1;

    spi_cfg_4.configuration_b.baud_rate = SPI_BAUD_RATE_CLK_DIV_2;
    spi_cfg_4.configuration_b.crc_en = SPI_HARDWARE_CRC_DISABLE;
    spi_cfg_4.configuration_b.data_frame = SPI_DATA_FRAME_FORMAT_8_BITS;
    spi_cfg_4.configuration_b.data_mode = SPI_DATA_MODE_0;
    spi_cfg_4.configuration_b.frame_format = SPI_FRAME_FORMAT_MSB_FIRST;
    spi_cfg_4.configuration_b.mode = SPI_MODE_SLAVE;
    spi_cfg_4.configuration_b.slave_select_mode = SPI_SLAVE_SELECT_MANUAL;
    spi_cfg_4.configuration_b.soft_slave_en = SPI_SOFTWARE_SLAVE_MANAGE_ENABLE;
    spi_cfg_4.configuration_b.dma_transmit_en = 0U;
    spi_cfg_4.configuration_b.dma_receive_en = 0U;
    spi_cfg_4.direction = SPI_DIRECTION_2_LINES_FULL_DUPLEX;
    spi_cfg_4.err_ipl = BSP_IRQ_DISABLE;
    spi_cfg_4.transmit_ipl = BSP_IRQ_DISABLE;
    spi_cfg_4.receive_ipl = 11U;
    spi_cfg_4.p_dma_rx_cfg = NULL;
    spi_cfg_4.p_dma_rx_ctrl = NULL;
    spi_cfg_4.p_dma_tx_cfg = NULL;
    spi_cfg_4.p_dma_tx_ctrl = NULL;
    spi_cfg_4.unit = SPI_UNIT_2;

    spi_cfg_dma_0.configuration_b.baud_rate = SPI_BAUD_RATE_CLK_DIV_256;
    spi_cfg_dma_0.configuration_b.crc_en = SPI_HARDWARE_CRC_DISABLE;
    spi_cfg_dma_0.configuration_b.data_frame = SPI_DATA_FRAME_FORMAT_8_BITS;
    spi_cfg_dma_0.configuration_b.data_mode = SPI_DATA_MODE_0;
    spi_cfg_dma_0.configuration_b.frame_format = SPI_FRAME_FORMAT_MSB_FIRST;
    spi_cfg_dma_0.configuration_b.mode = SPI_MODE_MASTER;
    spi_cfg_dma_0.configuration_b.slave_select_mode = SPI_SLAVE_SELECT_MANUAL;
    spi_cfg_dma_0.configuration_b.soft_slave_en = SPI_SOFTWARE_SLAVE_MANAGE_ENABLE;
    spi_cfg_dma_0.configuration_b.dma_transmit_en = 1U;
    spi_cfg_dma_0.configuration_b.dma_receive_en = 0U;
    spi_cfg_dma_0.direction = SPI_DIRECTION_2_LINES_FULL_DUPLEX;
    spi_cfg_dma_0.err_ipl = BSP_IRQ_DISABLE;
    spi_cfg_dma_0.transmit_ipl = BSP_IRQ_DISABLE;
    spi_cfg_dma_0.receive_ipl = BSP_IRQ_DISABLE;
    spi_cfg_dma_0.p_dma_rx_cfg = NULL;
    spi_cfg_dma_0.p_dma_rx_ctrl = NULL;
    spi_cfg_dma_0.p_dma_tx_cfg = &dma_spi_tx_cfg;
    spi_cfg_dma_0.p_dma_tx_ctrl = &dma_spi_tx_ctrl;
    spi_cfg_dma_0.unit = SPI_UNIT_1;

    spi_cfg_dma_1.configuration_b.baud_rate = SPI_BAUD_RATE_CLK_DIV_256;
    spi_cfg_dma_1.configuration_b.crc_en = SPI_HARDWARE_CRC_DISABLE;
    spi_cfg_dma_1.configuration_b.data_frame = SPI_DATA_FRAME_FORMAT_8_BITS;
    spi_cfg_dma_1.configuration_b.data_mode = SPI_DATA_MODE_0;
    spi_cfg_dma_1.configuration_b.frame_format = SPI_FRAME_FORMAT_MSB_FIRST;
    spi_cfg_dma_1.configuration_b.mode = SPI_MODE_SLAVE;
    spi_cfg_dma_1.configuration_b.slave_select_mode = SPI_SLAVE_SELECT_MANUAL;
    spi_cfg_dma_1.configuration_b.soft_slave_en = SPI_SOFTWARE_SLAVE_MANAGE_ENABLE;
    spi_cfg_dma_1.configuration_b.dma_transmit_en = 0U;
    spi_cfg_dma_1.configuration_b.dma_receive_en = 1U;
    spi_cfg_dma_1.direction = SPI_DIRECTION_2_LINES_FULL_DUPLEX;
    spi_cfg_dma_1.err_ipl = BSP_IRQ_DISABLE;
    spi_cfg_dma_1.transmit_ipl = BSP_IRQ_DISABLE;
    spi_cfg_dma_1.receive_ipl = BSP_IRQ_DISABLE;
    spi_cfg_dma_1.p_dma_rx_cfg = &dma_spi_rx_cfg;
    spi_cfg_dma_1.p_dma_rx_ctrl = &dma_spi_rx_ctrl;
    spi_cfg_dma_1.p_dma_tx_cfg = NULL;
    spi_cfg_dma_1.p_dma_tx_ctrl = NULL;
    spi_cfg_dma_1.unit = SPI_UNIT_2;
}

void spi_run_test(void)
{
    spi_set_up_test();
    spi_polling_test_case();
    spi_interrupt_test_case();
    spi_interrupt_test_case_1();
    spi_error_test_case();
    spi_dma_test_case();
}

#endif
