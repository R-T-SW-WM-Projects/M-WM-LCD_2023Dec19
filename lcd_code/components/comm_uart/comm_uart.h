/******************************************************************
* @Author   : ASHRAF (ashraf-masoud@elarabygroup.com)
* @Origin Date : 10 jan 2021
* @Version  : 1.0.0
*******************************************************************/

#ifndef COMM_UART_H
#define COMM_UART_H

/*********************
 *      INCLUDES
 *********************/
#include "../MCAL/mcal.h"

/*********************
 *      TYPEDEFS
 *********************/
typedef uart_t comm_uart_t;

/*********************
 *      DEFINES
 *********************/
#define COMM_UART_0  UART_NUM_0
#define COMM_UART_1  UART_NUM_1

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void comm_uart_init(comm_uart_t COMM_UART_x);
hal_err_t comm_uart_set_string(comm_uart_t COMM_UART_x, const char *const str);
uint8_t comm_uart_get_string(comm_uart_t COMM_UART_x, char* const buff, uint8_t buffsize);
hal_err_t comm_uart_set_bytes(comm_uart_t COMM_UART_x, const uint8_t *const buff, uint8_t buffsize);
uint8_t comm_uart_get_bytes(comm_uart_t COMM_UART_x, uint8_t* const buff, uint8_t buffsize);

#endif