#ifndef __FT6X06_H
/*
* Copyright © 2020 Wolfgang Christl

* Permission is hereby granted, free of charge, to any person obtaining a copy of this
* software and associated documentation files (the “Software”), to deal in the Software
* without restriction, including without limitation the rights to use, copy, modify, merge,
* publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons
* to whom the Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or
* substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
* PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
* FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#define __FT6X06_H

#include <stdint.h>
#include <stdbool.h>
#if CONFIG_LV_FT6X36_COORDINATES_QUEUE
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#endif
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif


/*********************
 *      DEFINES
 *********************/
#define FT6236_I2C_SLAVE_ADDR   0x38



/* Max detectable simultaneous touch points */
#define FT6X36_MAX_TOUCH_PNTS     2



typedef struct {
    bool inited;
} ft6x36_status_t;

typedef struct
{
  int16_t last_x;
  int16_t last_y;
  lv_indev_state_t current_state;
} ft6x36_touch_t;

#if CONFIG_LV_FT6X36_COORDINATES_QUEUE
extern QueueHandle_t ft6x36_touch_queue_handle;
#endif

void ft6x06_init(uint16_t dev_addr);
uint8_t ft6x36_get_gesture_id();
bool ft6x36_read(lv_indev_drv_t *drv, lv_indev_data_t *data);

#ifdef __cplusplus
}
#endif
#endif /* __FT6X06_H */
