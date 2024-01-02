/**
 * @file tt_scheduler.c
 * @author ASHRAF (ashraf-masoud@elarabygroup.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-16
 */
//TODO: add support for task args
/*********************
 *      INCLUDES
 *********************/
#include "tt_scheduler.h"
#include "tt_cfg.h"
#include <esp_task_wdt.h>
/**********************
 *      TYPEDEFS
 **********************/
typedef struct
{
   taskpointer pTask;       // Pointer to the task (must be a 'void (void)' function)
   volatile uint16_t delay;   // delay (ticks) until the function will (next) be run
   uint16_t period;           // Interval (ticks) between subsequent runs.
   uint8_t run_me;            // Incremented (by scheduler) when task is due to execute
} tcb_t;

/**********************
 * STATIC VARIABLES
 **********************/
static tcb_t tasks[TT_NUMBER_TASKS];    // The array of tasks
static uint32_t millis = 0;
static esp_timer_handle_t TT_TIMER;
/*********************
 *      DEFINES
 *********************/


/**********************
 *  STATIC PROTOTYPES
 **********************/
static void tt_scheduler(void*);
static uint8_t private_tt_delete_task(const uint8_t task_index);
static void tt_sleep(void);


/**********************
 * GLOBAL FUNCTIONS
 **********************/
/**
 * @brief 
 * Scheduler initialization function.  Prepares scheduler
 * data structures and sets up timer interrupts at required rate.
 * 
 * You must call this function before using the scheduler. 
 */
void tt_init(void)
{
   uint8_t i;
   assert(TT_TICK_MS);
   for (i = 0; i < TT_NUMBER_TASKS; i++)
   {
      private_tt_delete_task(i);
   }
#if TIMER_CALLBACK_USED
   /* Create and start a periodic timer interrupt to call lv_tick_inc */
   esp_timer_create_args_t periodic_timer_args = {
       .callback = &tt_scheduler,
       .name = "periodic_TT"};

   
   ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &TT_TIMER));
#endif
#if TIMER_ISR_USED

   timer_config_t tmr_cfg = {
       .timer_mode = TIMER_MODE_TIMER,
       .period_us = TT_TICK_MS*1000, //1 ms
   };
   timer_init(TT_TIMER, &tmr_cfg);

   interrupt_config_t int_cfg = {
      .state = ENABLE,
      .priority = INTERRUPT_PRIORITY_LVL_HIGHEST
   };
   millis = 0;
   timer_init_interrupt(TT_TIMER, &int_cfg);
   #endif
}


/**
 * @brief 
 * This is the 'dispatcher' function.  When a task (function)
 * is due to run, tt_dispatch_task() will run it.
 * This function must be called (repeatedly) from the main loop.
 */
void tt_dispatch_task(void)
{
   uint8_t i;

   // Dispatches (runs) the next task (if one is ready)
   for (i = 0; i < TT_NUMBER_TASKS; i++)
   {
      if (tasks[i].run_me > 0)
      {
         (*tasks[i].pTask)(); // Run the task

         tasks[i].run_me -= 1; // Reset / reduce run_me flag

         // Periodic tasks will automatically run again
         // - if this is a 'one shot' task, remove it from the array
         if (tasks[i].period == 0)
         {
            private_tt_delete_task(i);
         }
      }
   }
   // The scheduler enters idle mode at this point
   tt_sleep();
}


/**
 * @brief 
 * This is the scheduler ISR.  It is called at a rate 
 * determined by the timer settings in the 'init' function.
 */
void tt_scheduler(void* args)
{
   uint8_t i;
   millis++;
   // NOTE: calculations are in *TICKS* (not milliseconds)
   for (i = 0; i < TT_NUMBER_TASKS; i++)
   {
      // Check if there is a task at this location
      if (tasks[i].pTask)
      {
         if (tasks[i].delay == 0)
         {
            // The task is due to run
            tasks[i].run_me += 1; // Inc. the 'run_me' flag

            if (tasks[i].period)
            {
               // Schedule regular tasks to run again
               tasks[i].delay = tasks[i].period;
               tasks[i].delay -= 1;
            }
         }
         else
         {
            tasks[i].delay -= 1;
         }
      }
   }
   //TT_CLR_FLAG();
}


/**
 * @brief Causes a task (function) to be executed at regular intervals 
 * or after a user-defined delay
 * 
 * @param pFunction - The name of the function which is to be scheduled.
 * NOTE: All scheduled functions must be 'void, void' -
 *       that is, they must take no parameters, and have 
 *       a void return type. 
 * @param DELAY - The interval (TICKS) before the task is first executed
 * @param PERIOD -  If 'PERIOD' is 0, the function is only called once,
 *        at the time determined by 'DELAY'.  If PERIOD is non-zero,
 *        then the function is called repeatedly at an interval
 *        determined by the value of PERIOD (see below for examples
 *        which should help clarify this).
 * 
 * @return Returns the position in the task array at which the task has been 
 * added.
 * 
 * Task_ID = tt_add_task(Do_X,1000,0);
 * Causes the function Do_X() to be executed once after 1000 sch ticks.            
 * 
 * Task_ID = tt_add_task(Do_X,0,1000);
 * Causes the function Do_X() to be executed regularly, every 1000 sch ticks.            
 * 
 * Task_ID = tt_add_task(Do_X,300,1000);
 * Causes the function Do_X() to be executed regularly, every 1000 ticks.
 * Task will be first executed at T = 300 ticks, then 1300, 2300, etc.            
 * 
 */
uint8_t tt_add_task(taskpointer pFunction,
                     const uint16_t DELAY,
                     const uint16_t PERIOD)
{
   uint8_t i = 0;

   // First find a gap in the array (if there is one)
   while ((tasks[i].pTask != 0) && (i < TT_NUMBER_TASKS))
   {
      i++;
   }

   // Have we reached the end of the list?
   if (i == TT_NUMBER_TASKS)
   {
      // Task list is full
      return TT_NUMBER_TASKS;
   }

   // If we're here, there is a space in the task array
   tasks[i].pTask = pFunction;

   tasks[i].delay = DELAY;
   tasks[i].period = PERIOD/TT_TICK_MS;

   tasks[i].run_me = 0;

   return i; // return position of task (to allow later deletion)
}

/**
 * check if a task is scheduled.
 * @param pFunction: function pointer for the task.
 * @return true: if task is scheduled.
 *         false: if task is not scheduled.
 */
bool tt_get_taskstate(taskpointer pFunction)
{
   assert(pFunction);

   uint8_t i;
   for(i = 0; i < TT_NUMBER_TASKS; i++)
   {
      if(tasks[i].pTask == pFunction)
      {
         return true;
      }
   }
   return false;
}

/**
 * @brief 
 * Removes a task from the scheduler.  Note that this does
 * *not* delete the associated function from memory: 
 * it simply means that it is no longer called by the scheduler. 
 * @param pFunction 
 * @return 
 */
uint8_t tt_delete_task(taskpointer pFunction)
{
   assert(pFunction);
   uint8_t task_index;
   for (task_index = 0; task_index < TT_NUMBER_TASKS; task_index++)
   {
      if (tasks[task_index].pTask == pFunction)
      {
         tasks[task_index].pTask = 0x0000;
         tasks[task_index].delay = 0;
         tasks[task_index].period = 0;
         tasks[task_index].run_me = 0;
         return 0;
      }
   }
   return 0; // return status
}


/**
 * @brief Starts the scheduler, by enabling interrupts.
 * 
 */
void tt_start(void)
{
   //timer_cmd(TT_TIMER, ENABLE);
   ESP_ERROR_CHECK(esp_timer_start_periodic(TT_TIMER, TT_TICK_MS * 1000));

}

/**
 * @brief 
 * 
 * @param pFunction 
 * @param period_ms 
 * @return hal_err_t 
 */
hal_err_t tt_set_period(taskpointer pFunction,  const uint16_t period_ms)
{
   uint8_t task_index;
   for (task_index = 0; task_index < TT_NUMBER_TASKS; task_index++)
   {
      if (tasks[task_index].pTask == pFunction)
      {
         tasks[task_index].period = period_ms/TT_TICK_MS;
         return HAL_OK;
      }
   }
   return HAL_FAIL;
}


uint32_t tt_get_ticks()
{
   return millis;
}
/**********************
 *  STATIC FUNCTIONS
 **********************/
#define RETURN_NORMAL (uint8_t) 0
#define RETURN_ERROR (uint8_t) 1
/**
 * @brief 
 * Removes a task from the scheduler.  Note that this does
 * *not* delete the associated function from memory: 
 * it simply means that it is no longer called by the scheduler. 
 * @param task_index: The task index.  Provided by tt_add_task()
 * @return RETURN_ERROR or RETURN_NORMAL
 */
uint8_t private_tt_delete_task(const uint8_t task_index)
{
   uint8_t return_code;
   if (tasks[task_index].pTask == 0)
   {
      return_code = RETURN_ERROR;
   }
   else
   {
      return_code = RETURN_NORMAL;
   }
   tasks[task_index].pTask = 0x0000;
   tasks[task_index].delay = 0;
   tasks[task_index].period = 0;
   tasks[task_index].run_me = 0;

   return return_code; // return status
}
void call_idle_task()
{
  //ESP_LOGI(TAG,"idle");
    static uint8_t i = 0;
    vTaskDelay(10/portTICK_PERIOD_MS);
}


static void tt_sleep()
{
   //TODO:
}
