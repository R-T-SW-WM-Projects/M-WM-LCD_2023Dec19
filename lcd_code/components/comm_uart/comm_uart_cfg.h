#ifndef _COMM_UART_CFG_H
#define _COMM_UART_CFG_H
/*********************
 *    USER DEFINE
 *********************/
#define BUFF_SIZE   30

// typedef enum{
//     COMM_UART_1,
//     COMM_UART_2,
//     COMM_UART_SOFT,//NOT IMPLEMENTED TODO:
//     COMM_UART_MAX,
// }comm_uart_t;


/**
 * Specify the Max num of uart modules needed at the same time.
 * used for static memory allocation
 */
#define COMM_UART_USED_NUM   1




#endif
