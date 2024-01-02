
#ifndef __I2S_LCD_TYPES__
#define __I2S_LCD_TYPES__


#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "esp_heap_caps.h"
#include "esp32/rom/lldesc.h"
#include "soc/dport_access.h"
#include "soc/dport_reg.h"
#include "soc/i2s_struct.h"
#include "driver/i2s.h"

typedef struct {
    uint32_t node_cnt;
    uint32_t node_buffer_size;
    lldesc_t *descriptor;
    QueueHandle_t event_queue;
} dma_obj_t;

typedef struct {
    dma_obj_t dma;                      // 
    intr_handle_t i2s_intr_handle;      // Used to allocate and free the i2s ISR
    i2s_dev_t *i2s;                     // Core: structe map of i2s registers
} i2s_dma_obj_t;


typedef struct {
    i2s_dma_obj_t *i2s_dma_obj;
    SemaphoreHandle_t mutex;
} i2s_lcd_driver_t;

#endif