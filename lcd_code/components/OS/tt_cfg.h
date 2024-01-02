/**
 * Author: ASHRAF
 * 
 */

#ifndef TT_CONFIG_H
#define	TT_CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "esp_timer.h"

/**********************
 *      USER CONFIG
 **********************/
#if 0
#define TT_TIMER            TIMER2
#define TT_ISR(void)        TIMER2_ISR(void)
#define TT_CLR_FLAG(void)   TIMER2_CLR_FLAG(void)
#endif

#define TIMER_CALLBACK_USED 1


#define TT_TICK_MS          1
/**
* Defines number of tasks used in the system.
*/
#if defined(CONFIGURATION_FILE)
#define TT_NUMBER_TASKS   (SCH_NUM_TASKS)
#else
#define TT_NUMBER_TASKS (6)
#endif

#ifdef	__cplusplus
}
#endif

#endif
