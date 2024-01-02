

#include "uart.h"
#include "hal/uart_hal.h"
#include "driver/uart.h"

#if UART_0_FLOWCTR_ENABLED == 0
    #define UART_0_RTS  GPIO_PIN_NC    //user shouldn't change this value
    #define UART_0_CTS  GPIO_PIN_NC    //user shouldn't change this value
#endif

#if UART_1_FLOWCTR_ENABLED == 0
    #define UART_1_RTS  GPIO_PIN_NC    //user shouldn't change this value
    #define UART_1_CTS  GPIO_PIN_NC    //user shouldn't change this value
#endif



static uart_hal_context_t uart_driver[UART_NUM_MAX] = 
{
    {UART_LL_GET_HW(UART_NUM_0)},
   { UART_LL_GET_HW(UART_NUM_1)},
#if UART_NUM_MAX > 2
    UART_LL_GET_HW(UART_NUM_2),
#endif
};

typedef struct {
    int baud_rate;                      /*!< UART baud rate*/
    uart_word_length_t data_bits;       /*!< UART byte size*/
    uart_parity_t parity;               /*!< UART parity mode*/
    uart_stop_bits_t stop_bits;         /*!< UART stop bits*/
    uart_hw_flowcontrol_t flow_ctrl;    /*!< UART HW flow control mode (cts/rts)*/
    uint8_t rx_flow_ctrl_thresh;        /*!< UART HW RTS threshold*/
    union {
        uart_sclk_t source_clk;         /*!< UART source clock selection */
        bool use_ref_tick  __attribute__((deprecated)); /*!< Deprecated method to select ref tick clock source, set source_clk field instead */
    };
    int tx_io;
    int rx_io;
    int rts_io;
    int cts_io;

} mcal_uart_config_t;

/**
 * @brief 
 * 
 * @param uart_num UART port number
 */
void mcal_uart_init(uart_t uart_num)
{
    mcal_uart_config_t uart_config = {0};
    #if UART_0_ENABLED == 1
    if(uart_num == UART_NUM_0)
    {
        uart_config.baud_rate = UART_0_BAUDRATE;
        uart_config.data_bits = UART_0_WORD_LENGTH;
        uart_config.flow_ctrl = UART_0_FLOWCTR_ENABLED;
        uart_config.parity = UART_0_PARITY;
        uart_config.stop_bits = UART_0_STOP_BITS;
        uart_config.rx_flow_ctrl_thresh = 100;
        uart_config.tx_io = UART_0_TX;
        uart_config.rx_io = UART_0_RX;
        uart_config.rts_io = UART_0_RTS;
        uart_config.cts_io = UART_0_CTS;
    }
    #elif UART_1_ENABLED == 1
    if(uart_num == UART_NUM_1)
    {
        uart_config.baud_rate = UART_1_BAUDRATE;
        uart_config.data_bits = UART_1_WORD_LENGTH;
        uart_config.flow_ctrl = UART_1_FLOWCTR_ENABLED;
        uart_config.parity = UART_1_PARITY;
        uart_config.stop_bits = UART_1_STOP_BITS;
        uart_config.rx_flow_ctrl_thresh = 100;
        uart_config.tx_io = UART_1_TX;
        uart_config.rx_io = UART_1_RX;
        uart_config.rts_io = UART_1_RTS;
        uart_config.cts_io = UART_1_CTS;
    }
    #endif
    uart_hal_init(&uart_driver[uart_num], uart_num);
    uart_hal_set_baudrate(&uart_driver[uart_num], UART_SCLK_APB, uart_config.baud_rate);
    uart_hal_set_parity(&uart_driver[uart_num], uart_config.parity);
    uart_hal_set_data_bit_num(&uart_driver[uart_num], uart_config.data_bits);
    uart_hal_set_stop_bits(&uart_driver[uart_num], uart_config.stop_bits);
    uart_hal_set_tx_idle_num(&uart_driver[uart_num], 0);
    uart_hal_set_hw_flow_ctrl(&uart_driver[uart_num], uart_config.flow_ctrl, uart_config.rx_flow_ctrl_thresh);
    // The module reset do not reset TX and RX memory.
    // reset FIFO to avoid garbage data remained in the FIFO.
    uart_hal_rxfifo_rst(&uart_driver[uart_num]);
    uart_hal_txfifo_rst(&uart_driver[uart_num]);

    uart_set_pin(uart_num, uart_config.tx_io, uart_config.rx_io, uart_config.rts_io, uart_config.cts_io);

}


/**
 * @brief 
 * 
 * @param uart_num UART port number
 * @param data 
 * @return mcal_err_t 
 */
mcal_err_t mcal_uart_set_byte(uart_t uart_num, uart_data_t data)
{
    if(uart_ll_get_txfifo_len(uart_driver[uart_num].dev) == 0)
    {
        return MCAL_FAIL;
    }
    else
    {
        uart_ll_write_txfifo(uart_driver[uart_num].dev, &data, 1);
    }
    return MCAL_OK;
}

/**
 * @brief 
 * 
 * @param uart_num UART port number
 * @param data 
 * @return mcal_err_t 
 */
mcal_err_t mcal_uart_get_byte(uart_t uart_num, uart_data_t* data)
{
    if(uart_ll_get_rxfifo_len(uart_driver[uart_num].dev) == 0)
    {
        return MCAL_FAIL;
    }
    else
    {
        uart_ll_read_rxfifo(uart_driver[uart_num].dev, data, 1);
        return MCAL_OK;
    }
}

/**
 * @brief 
 * 
 * @param uart_num UART port number
 * @param buff 
 * @param size 
 * @return uint8_t 
 */
uint8_t mcal_uart_set_nbyte(uart_t uart_num,  uint8_t const * buff, uint8_t size)
{
    uint8_t written_size;
    uart_hal_write_txfifo(&uart_driver[uart_num], buff, size, &written_size);
    return size - written_size;
}

/**
 * 
 * @param uart_num UART port number
 * @param buff 
 * @param buff_size 
 * @return uint8_t :the size of data recieved in bytes
 */
uint8_t mcal_uart_get_nbyte(uart_t uart_num, uint8_t * const buff, uint8_t buff_size)
{
    int size;
    uart_hal_read_rxfifo(&uart_driver[uart_num], buff, &size);
    buff_size = size;
    return buff_size;
}


