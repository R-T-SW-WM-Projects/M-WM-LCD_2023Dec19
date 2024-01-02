/******************************************************************
* @Title    : TIME TRIGGERED Scheduler (TTSCH)                        
* @Filename : schedule.h                              
* @Author   : Ali Makhlouf        
              ASHRAF                     
* @Origin Date : 07/07/2021                                                                    
* @Version  : 1.0.0                                                                           
* @Compiler : GCC                                                                     
* @brief    : This file contains the prototypes of the SCH Module                                    
*******************************************************************/
#ifndef TT_SCH_H		         
#define TT_SCH_H		       

#define TAG "main"

/*********************
 *      INCLUDES
 *********************/   
#include "hal_err.h"
#include "tt_cfg.h"

#define LV_TICK_PERIOD_MS 1

/**********************
 *      TYPEDEFS
 **********************/
typedef void (*taskpointer)(void);

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void tt_init(void);
void tt_start(void);
void tt_dispatch_task(void);
uint8_t tt_add_task(taskpointer pFunction,
                     const uint16_t DELAY,
                     const uint16_t PERIOD);  
hal_err_t tt_set_period(taskpointer pFunction,  const uint16_t period_ms);
bool tt_get_taskstate(taskpointer pFunction);
uint8_t tt_delete_task(taskpointer pFunction);
uint32_t tt_get_ticks();

void call_idle_task();




#endif
                              
