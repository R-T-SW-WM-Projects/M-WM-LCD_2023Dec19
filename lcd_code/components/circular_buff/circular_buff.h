/**
 * @file circular_buff.h
 * @author ASHRAF (ashraf-masoud@elarabygroup.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _CIRCULAR_BUFF_H
#define _CIRCULAR_BUFF_H

/*********************
 *      INCLUDES
 *********************/
#include "../MCAL/mcal.h"
#include "../hal_err.h"


/*********************
 *    USER DEFINE
 *********************/
typedef uint8_t cbuff_data_t;

/********************* 
 *     Typedefs
*********************/
typedef uint8_t cbuff_iterator_t;

typedef struct {
	//private attributes
	//should not be accessed directly by user
	cbuff_data_t * buffer;
	cbuff_iterator_t head;  // head points to the next available space
	cbuff_iterator_t tail;  // tail points to the current available data in FIFO maner
	cbuff_iterator_t size;  // of the buffer
	bool full;
} circularbuff_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void circularbuff_init(circularbuff_t* const me, cbuff_data_t* buff, uint8_t buff_size);
void circularbuff_reset(circularbuff_t* const me);
bool circularbuff_isfull(circularbuff_t* const me);
bool circularbuff_isempty(circularbuff_t* const me);
uint8_t circularbuff_get_capacity(circularbuff_t* const me);
uint8_t circularbuff_get_size(circularbuff_t* const me);
hal_err_t circularbuff_set_data(circularbuff_t* const me, cbuff_data_t const data);
hal_err_t circularbuff_get_data(circularbuff_t* const me, cbuff_data_t* data);
hal_err_t circularbuff_remove_lastelement(circularbuff_t* const me);
bool circularbuff_get_state(circularbuff_t* const me);


#endif