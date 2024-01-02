/**
 * @file circular_buff.c
 * @author ASHRAF (ashraf-masoud@elarabygroup.com)
 * @version 0.1
 * @date 2022-01-09
 * @brief This file provides implementation to create and manage the circular buffer objs.
 */

/*********************
 *      INCLUDES
 *********************/
#include "circular_buff.h"


/**********************
 * GLOBAL FUNCTIONS
 **********************/
/**
 * @brief 
 * 
 * @param me: pointer to the circularbuff obj
 * @param buff: 
 * @param buff_size: 
 */
void circularbuff_init(circularbuff_t* const me, cbuff_data_t* buff, uint8_t buff_size)
{
	assert(me && buff && buff_size);

	me->buffer = buff;
	me->size = buff_size;
	circularbuff_reset(me);
}

/**
 * resets the Circular buffer obj to empty state
 * @param me: pointer to the circularbuff obj
 */
void circularbuff_reset(circularbuff_t* const me)
{
    assert(me);

    me->head = 0;
    me->tail = 0;
    me->full = false;
}

/**
 * 
 * @param me: pointer to the circularbuff obj
 * @return -true 
 *         -false
 */
bool circularbuff_isfull(circularbuff_t* const me)
{
    assert(me);
    return me->full;
}


/**
 * 
 * @param me: pointer to the circularbuff obj
 * @return -true 
 *         -false
 */
bool circularbuff_isempty(circularbuff_t* const me)
{
    assert(me);
    return (!me->full && (me->head == me->tail));
}


/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t circularbuff_get_capacity(circularbuff_t* const me)
{
	assert(me);

	return me->size;
}

/**
 * @brief 
 * 
 * @param me 
 * @return uint8_t 
 */
uint8_t circularbuff_get_size(circularbuff_t* const me)
{
	assert(me);

	size_t size = me->size;

	if(!me->full)
	{
		if(me->head >= me->tail)
		{
			size = (me->head - me->tail);
		}
		else
		{
			size = (me->size - (me->tail - me->head));
		}
	}

	return size;
}
/**
 * @param me: pointer to the circularbuff obj
 * @param data :data to store
 * @return HAL_FAIL if the buffer is FULL,
 *  HAL_OK if success write
 */
hal_err_t circularbuff_set_data(circularbuff_t* const me, cbuff_data_t const data)
{
	assert(me && me->buffer);
    if(circularbuff_isfull(me))
    {
        return HAL_FAIL;
    }
    me->buffer[me->head] = data;
    //advance iterator
    me->head++;
	if (me->head == me->size) 
	{
		me->head = 0;
	}
    me->full = (me->head == me->tail);
    return HAL_OK;
}




/**
 * read and remove (Pop) the next element of the specified circuler buffer 
 * @param me: pointer to the circularbuff obj
 * @param data: address of the data holder variable
 * @return HAL_FAIL if the buffer is empty,
 *  HAL_OK if success
 */
hal_err_t circularbuff_get_data(circularbuff_t* const me, cbuff_data_t* data)
{
    assert(me && me->buffer && data);

    if(circularbuff_isempty(me))
    {
        return HAL_FAIL;
    }

    //get the data
    *data = me->buffer[me->tail];
    //clear full flag
    me->full = false;
    //advance iterator
    me->tail++;
    if(me->tail == me->size)
    {
        me->tail = 0;
    }

    return HAL_OK;
}

/**
 * @brief 
 * Remove the last element pushed to the cbuff
 * | 5 |<- head  ||  | 5 |
 * | 6 |         ||  | 6 |<- head
 * @param me: pointer to the circularbuff obj
 * @return hal_err_t 
 */
hal_err_t circularbuff_remove_lastelement(circularbuff_t* const me)
{
    assert(me);
    if(me->tail == me->head)  // if empty
    {
        return HAL_FAIL;
    }
    if(me->head == 0)
    {
        me->head = me->size-1;
    }
    else
    {
        me->head --;
    }
    return HAL_OK;
}

