#ifndef _SPI_H_
#define _SPI_H_

#include "bsp_api.h"
#include "dma.h"

/* Bit mask for Overrun error */
#define SPI_ERROR_OVERRUN_BIT_MASK (1U << 6)

/* Bit mask for Mode Fault error */
#define SPI_ERROR_MODE_FAULT_BIT_MASK (1U << 5)

/* Bit mask for CRC error */
#define SPI_ERROR_CRC_BIT_MASK (1U << 4)

/**
 * @brief SPI Unit
 */
typedef enum e_spi_unit
{
    SPI_UNIT_1,
    SPI_UNIT_2,
#if (BSP_FEATURE_SPI3_IS_AVAILABLE)
    SPI_UNIT_3
#endif
} spi_unit_t;

/**
 * @brief SPI data Mode Configuration Table
 * | Mode | CPOL | CPHA | Idle State | Clock Phase / Data Behavior                         |
 * |------|------|------|------------|-----------------------------------------------------|
 * |  0   |  0   |  0   | Logic Low  | Sample on Rising Edge, Shift out on Falling Edge    |
 * |  1   |  0   |  1   | Logic Low  | Sample on Falling Edge, Shift out on Rising Edge    |
 * |  2   |  1   |  0   | Logic High | Sample on Falling Edge, Shift out on Rising Edge    |
 * |  3   |  1   |  1   | Logic High | Sample on Rising Edge, Shift out on Falling Edge    |
 */

/**
 * @brief SPI Data Mode
 */
typedef enum e_spi_data_mode
{
    SPI_DATA_MODE_0, /* CPOL = 0 CPHA = 0 */
    SPI_DATA_MODE_1, /* CPOL = 0 CPHA = 1 */
    SPI_DATA_MODE_2, /* CPOL = 1 CPHA = 0 */
    SPI_DATA_MODE_3  /* CPOL = 1 CPHA = 1 */
} spi_data_mode_t;

/**
 * @brief SPI Mode
 */
typedef enum e_spi_mode
{
    SPI_MODE_SLAVE,
    SPI_MODE_MASTER
} spi_mode_t;

/**
 * @brief SPI Baud Rate
 */
typedef enum e_spi_baud_rate
{
    SPI_BAUD_RATE_CLK_DIV_2,
    SPI_BAUD_RATE_CLK_DIV_4,
    SPI_BAUD_RATE_CLK_DIV_8,
    SPI_BAUD_RATE_CLK_DIV_16,
    SPI_BAUD_RATE_CLK_DIV_32,
    SPI_BAUD_RATE_CLK_DIV_64,
    SPI_BAUD_RATE_CLK_DIV_128,
    SPI_BAUD_RATE_CLK_DIV_256
} spi_baud_rate_t;

/**
 * @brief SPI Frame Format
 */
typedef enum e_spi_frame_format
{
    SPI_FRAME_FORMAT_MSB_FIRST,
    SPI_FRAME_FORMAT_LSB_FIRST
} spi_frame_format_t;

/**
 * @brief SPI Software Slave Management
 */
typedef enum e_spi_software_slave_manage
{
    SPI_SOFTWARE_SLAVE_MANAGE_DISABLE, ///< Hardware check the actual NSS pin status
    SPI_SOFTWARE_SLAVE_MANAGE_ENABLE ///< Hardware check the status of SSI bit (ignore actual pin status)
} spi_software_slave_manage_t;

/**
 * @brief SPI Data Frame Format
 */
typedef enum e_spi_data_frame_format
{
    SPI_DATA_FRAME_FORMAT_8_BITS,
    SPI_DATA_FRAME_FORMAT_16_BITS
} spi_data_frame_format_t;

/**
 * @brief SPI Hardware CRC
 */
typedef enum e_spi_hardware_crc
{
    SPI_HARDWARE_CRC_DISABLE,
    SPI_HARDWARE_CRC_ENABLE
} spi_hardware_crc_t;

/**
 * @brief SPI direction
 */
typedef enum e_spi_direction
{
    SPI_DIRECTION_2_LINES_FULL_DUPLEX = 0U,
    SPI_DIRECTION_2_LINES_RECEIVE_ONLY = 1U << 10,
    SPI_DIRECTION_1_LINE_RECEIVE_ONLY = 1U << 15,
    SPI_DIRECTION_1_LINE_TRANSMIT_ONLY = (1U << 15) | (1U << 14)
} spi_direction_t;

/**
 * @brief SPI Slave Select Mode (auto / manual use NSS pin)
 */
typedef enum e_spi_slave_select
{
    SPI_SLAVE_SELECT_MANUAL, ///< Slave Select manually (can work with multiple slaves)
    SPI_SLAVE_SELECT_AUTO ///< Slave Select automatically (can't work with multiple slaves)
} spi_slave_select_t;

/**
 * @brief SPI user Callback status
 */
typedef enum e_spi_callback_status
{
    SPI_CALLBACK_STATUS_NONE, ///< Default status
    SPI_CALLBACK_STATUS_TRANSMIT_COMPLETE, ///< Transmit complete
    SPI_CALLBACK_STATUS_RECEIVE_COMPLETE, ///< Receive complete
    SPI_CALLBACK_STATUS_MASTER_MODE_FAULT, ///< Master mode fault
    SPI_CALLBACK_STATUS_OVERRUN, ///< Overun condition
    SPI_CALLBACK_STATUS_CRC_ERROR ///< CRC error
} spi_callback_status_t;

/**
 * @brief SPI Configuration Structure
 */
typedef struct st_spi_cfg
{
    union
    {
        uint16_t configuration;
        struct
        {
            uint16_t data_mode : 2; ///< Data Mode
            uint16_t mode : 1; ///< Mode (Master / Slave)
            uint16_t baud_rate : 3; ///< Baud rate
            uint16_t frame_format : 1; ///< Frame format (MSB / LSB first)
            uint16_t soft_slave_en : 1; ///< Software Slave Management enable
            uint16_t data_frame : 1; ///< Data Frame Format (8 / 16 bits)
            uint16_t crc_en : 1; ///< Hardware CRC enable
            uint16_t slave_select_mode : 1; ///< Slave select mode (manual / auto)
            uint16_t dma_transmit_en : 1; ///< DMA Transmit enable
            uint16_t dma_receive_en : 1; ///< DMA Receive enable
        } configuration_b;
    };
    uint16_t direction; ///< SPI direction
    uint8_t transmit_ipl; ///< Transmit interrupt priority
    uint8_t receive_ipl; ///< Receive interrupt priority
    uint8_t err_ipl; ///< Error interrupt priority
    spi_unit_t unit; ///< SPI Unit
    void * p_dma_tx_ctrl; ///< Pointer to DMA TX control struct
    void * p_dma_tx_cfg; ///< Pointer to DMA TX configuration struct
    void * p_dma_rx_ctrl; ///< Pointer to DMA RX control struct
    void * p_dma_rx_cfg; ///< Pointer to DMA RX configuration struct
} spi_cfg_t;

/**
 * @brief SPI control structure. This struct will be set up by function.
 * Do not manually change the value of this struct.
 */
typedef struct st_spi_ctrl
{
    const spi_cfg_t *p_cfg; ///< Pointer to configuration struct
    SPIx_Type *p_reg; ///< Pointer to SPI register
    void (*p_callback)(void *p_args); ///< Poiter to user callback function
    void * p_src; ///< Poiter to source address
    void * p_dest; ///< Poiter to destination address
    uint32_t open; ///< Open status
    uint16_t write_size; ///< Size of the data to be write
    uint16_t read_size; ///< Size of the data to be read
    spi_callback_status_t callback_status; ///< The status of callback
} spi_ctrl_t;

void SPI_Open(spi_ctrl_t *p_ctrl, const spi_cfg_t *p_cfg);
void SPI_CallbackSet(spi_ctrl_t *p_ctrl, void (*p_callback)(void *p_args));
void SPI_Write(spi_ctrl_t *p_ctrl, void * p_src, uint16_t size);
void SPI_PollingWrite (spi_ctrl_t *p_ctrl, void *data);
void SPI_Read(spi_ctrl_t *p_ctrl, void * p_dest, uint16_t size);
void SPI_PollingRead (spi_ctrl_t *p_ctrl, void *data);
void SPI_Close(spi_ctrl_t *p_ctrl);

#endif
