#ifndef _UART_H
#define _UART_H
/*********************
 *      INCLUDES
 *********************/
#include "uart_const.h"
#include "mcal.h"
#include "mcal_err.h"
#include "driver/uart.h"

typedef uart_port_t uart_t;
/**********************
 * GLOBAL PROTOTYPES
 **********************/
void mcal_uart_init(uart_t UARTx);
mcal_err_t mcal_uart_set_byte(uart_t UARTx, uint8_t data);
mcal_err_t mcal_uart_get_byte(uart_t UARTx, uint8_t* data);
uint8_t mcal_uart_set_nbyte(uart_t uart_num,  uint8_t const * buff, uint8_t size);
uint8_t mcal_uart_get_nbyte(uart_t uart_num, uint8_t * const buff, uint8_t buff_size);
mcal_err_t mcal_uart_set_baudrate(uart_t UARTx, uint16_t baudrate);
//inline uart_bufferstatus_t mcal_uart_get_txbufferstatus(uart_t* UARTx);
//inline uart_bufferstatus_t mcal_uart_get_rxbufferstatus(uart_t* UARTx);



#endif