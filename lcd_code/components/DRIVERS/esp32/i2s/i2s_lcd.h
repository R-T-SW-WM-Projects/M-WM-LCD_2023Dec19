// Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#ifndef   __I2S_LCD_DRIVER_H__
#define   __I2S_LCD_DRIVER_H__

#include "driver/i2s.h"
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_heap_caps.h"
#include "esp32/rom/lldesc.h"
#include "soc/dport_access.h"
#include "soc/dport_reg.h"
#include "soc/i2s_struct.h"
#include "hal/gpio_ll.h"
#include "esp_log.h"

#ifdef __cplusplus
extern "C"
{
#endif



/**********************
 *      TYPEDEFS
 **********************/
typedef void * i2s_lcd_handle_t; /** Handle of i2s lcd driver */

/**
 * @brief Configuration of i2s lcd mode
 * 
 */
typedef struct {
    int8_t data_width;           /*!< Parallel data width, 16bit or 8bit available */
    int8_t pin_data_num[16];     /*!< Parallel data output IO*/
    int8_t pin_num_cs;           /*!< CS io num */
    int8_t pin_num_wr;           /*!< Write clk io*/
    int8_t pin_num_rs;           /*!< RS io num */
    int clk_freq;                /*!< I2s clock frequency */
    i2s_port_t i2s_port;         /*!< I2S port number */
    bool swap_data;              /*!< Swap the 2 bytes of RGB565 color */
    uint32_t buffer_size;        /*!< DMA buffer size */
} i2s_lcd_config_t;


typedef struct {
    uint32_t dma_buffer_size;
    uint32_t dma_half_buffer_size;
    uint32_t dma_node_buffer_size;
    uint32_t dma_node_cnt;
    uint32_t dma_half_node_cnt;
    lldesc_t *dma;
    uint8_t  *dma_buffer;
    QueueHandle_t event_queue;
    uint8_t width;
    bool swap_data;
} lcd_obj_t;

typedef struct {
    lcd_obj_t lcd;
    intr_handle_t lcd_cam_intr_handle;
    i2s_dev_t *i2s_dev;
} lcd_cam_obj_t;

typedef struct {
    void (*i2s_write_data_func)(lcd_cam_obj_t *lcd_cam_obj, uint8_t *data, size_t len);
    int rs_io_num;
    lcd_cam_obj_t *lcd_cam_obj;
    SemaphoreHandle_t mutex;
} i2s_lcd_driver_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/
i2s_lcd_handle_t i2s_lcd_driver_init(const i2s_lcd_config_t *config);
esp_err_t i2s_lcd_driver_deinit(i2s_lcd_handle_t handle);
esp_err_t i2s_lcd_write_data(i2s_lcd_handle_t handle, uint16_t data);
esp_err_t i2s_lcd_write_cmd(i2s_lcd_handle_t handle, uint16_t cmd);
esp_err_t i2s_lcd_write(i2s_lcd_handle_t handle, const uint8_t *data, uint32_t length);
esp_err_t i2s_lcd_acquire(i2s_lcd_handle_t handle);
esp_err_t i2s_lcd_release(i2s_lcd_handle_t handle);


#ifdef __cplusplus
}
#endif

#endif
