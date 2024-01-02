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



#ifdef __cplusplus
extern "C"
{
#endif

typedef void * i2s_lcd_handle_t; /** Handle of i2s dma driver */

/**
 * @brief Configuration of i2s dma mode
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
    uint32_t max_buffer_size;        /*!< DMA Max buffer size */
} i2s_lcd_config_t;


/**********************
 *  GLOBAL PROTOTYPES
 **********************/
i2s_lcd_handle_t i2s_lcd_driver_init(const i2s_lcd_config_t *config);
esp_err_t i2s_lcd_driver_deinit(i2s_lcd_handle_t handle);
void i2s_lcd_write_data(i2s_lcd_handle_t handle, uint8_t *data, size_t len);
esp_err_t i2s_lcd_acquire(i2s_lcd_handle_t handle);
esp_err_t i2s_lcd_release(i2s_lcd_handle_t handle);
void i2s_int_register(void (*func_ptr)(void));


#ifdef __cplusplus
}
#endif

#endif
