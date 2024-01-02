/********************************************************************************
 * @file    uart.c
 * @author  ASHRAF (ashraf-masoud@elarabygroup.com)
 * @version V1
 * @date    10-JAN-2022
 * @brief   This file provides Communication layer implementation to
 *          the uart communication module.
 */

/*********************
 *      INCLUDES
 *********************/
#include "..\circular_buff\circular_buff.h"
#include "comm_uart_cfg.h"
#include "comm_uart.h"
#include "uart.h"
#include "..\OS\tt_scheduler.h"
#include <esp_log.h>
/**********************
 *      Typedefs
 **********************/
typedef struct
{
    cbuff_data_t tx_cbuff[BUFF_SIZE];
    cbuff_data_t rx_cbuff[BUFF_SIZE];
    circularbuff_t txcbuff_obj;
    circularbuff_t rxcbuff_obj;
} comm_uart_config_t;

/**********************
 *  STATIC VARIABLES
 **********************/
static comm_uart_config_t cbuff_objs[COMM_UART_USED_NUM];

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void comm_uart0_set_byte(void);
static void comm_uart0_get_byte(void);

static void comm_uart1_set_byte(void);
static void comm_uart1_get_byte(void);

/**********************
 *  GLOBAL FUNCTIONS
 **********************/

/**
 * Set UART configuration parameters.
 * init module buffer
 * @param COMM_UART_x
 * @param uart_config
 */
void comm_uart_init(comm_uart_t COMM_UART_x)
{
    switch (COMM_UART_x)
    {
    case COMM_UART_0:
        tt_add_task(comm_uart0_get_byte, 1, 1);
        break;
    case COMM_UART_1:
        tt_add_task(comm_uart1_get_byte, 1, 1);
        break;

    }
    // init uart hardware module
    mcal_uart_init(COMM_UART_x);
    // init 2 (TX & RX) circular buffer objs
    circularbuff_init(&cbuff_objs[COMM_UART_x].txcbuff_obj, cbuff_objs[COMM_UART_x].tx_cbuff, BUFF_SIZE);
    circularbuff_init(&cbuff_objs[COMM_UART_x].rxcbuff_obj, cbuff_objs[COMM_UART_x].rx_cbuff, BUFF_SIZE);
}

/**
 * Write Null-terminated String to the uart buffer
 * @param COMM_UART_x: UART port number, the max port number is (COMM_UART_MAX -1)
 * @param str: Null terminated string address.
 * @return -HAL_OK if the write is successful.
 *         -HAL_FAIL if buffer overflow & any data written to the buffer is automatically removed.
 */
hal_err_t comm_uart_set_string(comm_uart_t COMM_UART_x, const char *const str)
{
    switch (COMM_UART_x)
    {
    case COMM_UART_0:
        if (tt_get_taskstate(comm_uart0_set_byte) == false)
        {
            tt_add_task(comm_uart0_set_byte, 1, 1);
        }
        break;
    case COMM_UART_1:
        if (tt_get_taskstate(comm_uart1_set_byte) == false)
        {
            tt_add_task(comm_uart1_set_byte, 1, 1);
        }
        break;
    }
    // write data to the Tx Cbuff
    int8_t i = 0;
    while (str[i] != '\0') // while not a null '\0'
    {
        // if the buffer couldn't hold the full string
        if (circularbuff_set_data(&cbuff_objs[COMM_UART_x].txcbuff_obj, str[i]) == HAL_FAIL)
        {
            //remove the string from the buff and report error
            for (; i >= 0; i--)
            {
                assert(circularbuff_remove_lastelement(&cbuff_objs[COMM_UART_x].txcbuff_obj) == HAL_OK);
            }
            return HAL_FAIL;
        }
        i++;
    }
    return HAL_OK;
}

/**
 * UART Read Null-terminated String from UART buffer
 * @param COMM_UART_x: UART port number, the max port number is (COMM_UART_MAX -1)
 * @param buff: data buffer address.
 * @param buffsize: data length to get.
 * @return num of char read from the UART buff.
 */
uint8_t comm_uart_get_string(comm_uart_t COMM_UART_x, char *const buff, uint8_t buffsize)
{
    cbuff_data_t data;
    uint8_t index = 0;
    //todo: try for loop over cbuff size
    while (circularbuff_get_data(&cbuff_objs[COMM_UART_x].rxcbuff_obj, &data) == HAL_OK &&
           index < buffsize)
    {
        if (data == '\0')
        {
            break;
        }
        buff[index] = data;
        index++;
    }
    return index;
}

/**
 * Send data to the UART port from a given buffer and length
 * @param COMM_UART_x: UART port number, the max port number is (COMM_UART_MAX -1).
 * @param buff: data buffer address.
 * @param buffsize: data length to send.
 * @return -HAL_OK if successful.
 *         -HAL_FAIL if buffer overflow & any data written to the buffer is automatically removed.
 */
hal_err_t comm_uart_set_bytes(comm_uart_t COMM_UART_x, const uint8_t *const buff, uint8_t buffsize)
{
    switch (COMM_UART_x)
    {
    case COMM_UART_0:
        if (tt_get_taskstate(comm_uart0_set_byte) == false)
        {
            tt_add_task(comm_uart0_set_byte, 1, 1);
        }
        break;
    case COMM_UART_1:
        if (tt_get_taskstate(comm_uart1_set_byte) == false)
        {
            tt_add_task(comm_uart1_set_byte, 1, 1);
        }
        break;
    }

    int8_t i;
    for (i = 0; i < buffsize; i++)
    {
        if (circularbuff_set_data(&cbuff_objs[COMM_UART_x].txcbuff_obj, buff[i]) == HAL_FAIL)
        {
            for (; i >= 0; i--)
            {
                assert(circularbuff_remove_lastelement(&cbuff_objs[COMM_UART_x].txcbuff_obj) == HAL_OK);
            }
            return HAL_FAIL;
        }
    }
    return HAL_OK;
}

/**
 * Read bytes from UART buffer.
 * @param COMM_UART_x: UART port number, the max port number is (COMM_UART_MAX -1).
 * @param buff: data buffer address.
 * @param buffsize: data length to read.
 * @return num of bytes read from the UART buff.
 */
uint8_t comm_uart_get_bytes(comm_uart_t COMM_UART_x, uint8_t *const buff, uint8_t buffsize)
{
    cbuff_data_t data;
    uint8_t index;
    for (index = 0; index < buffsize; index++)
    {
        if (circularbuff_get_data(&cbuff_objs[COMM_UART_x].rxcbuff_obj, &data) == HAL_OK)
        {
            buff[index] = data;
        }
        else
        {
            break;
        }
    }
    return index;
}

/**
 * @brief
 *
 * @param COMM_UART_x:
 * @return uart_event_t
 */

/**********************
 *  STATIC FUNCTIONS
 **********************/

// periodic task
/**
 * @brief
 *
 */
static void comm_uart0_set_byte(void)
{
    cbuff_data_t data;
    while (1)
    {
        if (circularbuff_get_data(&cbuff_objs[COMM_UART_0].txcbuff_obj, &data) == HAL_OK)
        {
            if(mcal_uart_set_byte(UART_NUM_0, data) != MCAL_OK)
            {
                return;
            }
        }
        else  //buff is empty
        {
            tt_delete_task(comm_uart0_set_byte);
            return;
        }
    }
    
    // todo: add timeout to the task
}

/**
 * @brief
 *
 */
static void comm_uart0_get_byte(void)
{
    cbuff_data_t data;
    while (mcal_uart_get_byte(UART_NUM_0, &data) == MCAL_OK)
    {
        if (circularbuff_set_data(&cbuff_objs[COMM_UART_0].rxcbuff_obj, data) == HAL_FAIL)
        {
            return;
        }
    }
    // todo: add timeout
}

static void comm_uart1_get_byte(void)
{
    cbuff_data_t data;
    while (mcal_uart_get_byte(UART_NUM_1, &data) == MCAL_OK)
    {
        if (circularbuff_set_data(&cbuff_objs[COMM_UART_1].rxcbuff_obj, data) == HAL_FAIL)
        {
            return;
        }
    }
}

static void comm_uart1_set_byte(void)
{
    cbuff_data_t data;
    while (circularbuff_get_data(&cbuff_objs[COMM_UART_1].txcbuff_obj, &data) == HAL_OK &&
           mcal_uart_set_byte(UART_NUM_1, data) != MCAL_FAIL)
    {
    }
}

// static void comm_uart_set_byte(void * args)
// {
//     comm_uart_t COMM_UART_x = (comm_uart_t)args;
//     uart_t* UARTx;
//     switch (COMM_UART_x)
//     {
//     case COMM_UART_1:
//         UARTx = UART_NUM_0;
//         break;
//     case COMM_UART_1:
//         UARTx = UART_NUM_1;
//         break;
//     }
//     cbuff_data_t data;
//     while(circularbuff_get_data(&cbuff_objs[COMM_UART_x].txcbuff_obj, &data) == HAL_OK
//           &&
//           uart_set_byte(UARTx, data) != DRIVER_FAIL);

// }