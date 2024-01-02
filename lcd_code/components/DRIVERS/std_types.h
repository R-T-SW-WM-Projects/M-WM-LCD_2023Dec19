/**
 * @file    STD_TYPE.h
 * @brief   Standard Types header file 
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_
/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include <stddef.h>
#include "driver_err.h"
#include <stdbool.h>
#include <assert.h>
#include <math.h>
//#include "utils.h"

/*********************
 *      DEFINES
 *********************/
#define HIGH            1
#define LOW             0

#define ON              1
#define OFF             0
typedef enum
{
    DISABLE = 0,
    ENABLE = 1
} functional_state_t;



#endif /* STD_TYPE_H_ */
