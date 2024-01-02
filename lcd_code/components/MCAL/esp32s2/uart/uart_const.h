
#ifndef _UART_CONST_H
#define _UART_CONST_H
#include "uart_cfg.h"

#define UART_DATASIZE_8   UART_DATA_8_BITS

#if UART_0_WORD_LENGTH > UART_DATASIZE_8
    typedef uint16_t uart_data_t;
#else
    typedef uint8_t uart_data_t;
#endif

// typedef enum {
//     UART_BUFFER_EMPTY     = 0x0,
//     UART_BUFFER_NOT_EMPTY = 0x1,
//     UART_BUFFER_NOT_FULL  = 0x1,
//     UART_BUFFER_FULL      = 0x2,
//     UART_BUFFER_OVERFLOW  = 0x3         // for RX only
// } uart_bufferstatus_t;

#endif
