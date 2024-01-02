// Copyright 2015-2020 Espressif Systems (Shanghai) PTE LTD
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

#include "sdkconfig.h"

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "driver/i2s.h"
#include "driver/periph_ctrl.h"
#include "esp_heap_caps.h"
#include "esp32s2/rom/lldesc.h"
#include "soc/system_reg.h"
#include "i2s_lcd.h"

#include "freertos/queue.h"
#include "soc/dport_access.h"
#include "soc/dport_reg.h"
#include "soc/i2s_struct.h"
#include "hal/gpio_ll.h"
#include "soc/periph_defs.h"
#include "i2s_lcd_types.h"
#include <math.h>


static const char *TAG = "ESP32S2_I2S_LCD";

#define I2S_CHECK(a, str, ret) if (!(a)) {                                              \
        ESP_LOGE(TAG,"%s:%d (%s):%s", __FILE__, __LINE__, __FUNCTION__, str);       \
        return (ret);                                                                   \
    }

#define DMA_NODE_BUFFER_MAX_SIZE  (4000) // 4-byte aligned
#define LCD_DATA_MAX_WIDTH (24)  /*!< Maximum width of LCD data bus */


/**********************
 *  STATIC VARIABLES
 **********************/
void (*i2s_isr_func)(void) = NULL;


/**********************
 *  STATIC PROTOTYPES
 **********************/

static void IRAM_ATTR i2s_isr(void *arg);
static esp_err_t i2s_dma_init(i2s_lcd_driver_t *drv, const i2s_lcd_config_t *config);
static void lcd_i2s_start(i2s_dev_t *i2s, uint32_t addr);
static esp_err_t i2s_reg_config(i2s_dev_t *i2s, uint16_t data_width, uint32_t clk_freq);
static esp_err_t lcd_set_pin(const i2s_lcd_config_t *config);
static esp_err_t dma_init_desc(dma_obj_t *dma, uint8_t* buff, size_t len);
static esp_err_t dma_init(dma_obj_t *dma_obj, uint32_t max_dma_buffer_size);
static esp_err_t i2s_dma_deinit(i2s_lcd_driver_t *drv);



/**********************
 *  GLOBAL FUNCTIONS
 **********************/

void i2s_int_register(void (*func_ptr)(void))
{
    ESP_LOGI(TAG, "interr register");
    if(func_ptr)
    {
        i2s_isr_func = func_ptr;
    }
    else
    {
        ESP_LOGW(TAG, "NULL POINTER FOUND");
    }
}

/**
 * @brief Initialize i2s dma driver.
 *
 * @param config configuration of i2s
 *
 * @return  A handle to the created i2s dma driver, or NULL in case of error.
 */
i2s_lcd_handle_t i2s_lcd_driver_init(const i2s_lcd_config_t *config)
{
    //assertions
    I2S_CHECK(NULL != config, "config pointer invalid", NULL);
    I2S_CHECK(GPIO_IS_VALID_GPIO(config->pin_num_wr), "GPIO WR invalid", NULL);
    I2S_CHECK(GPIO_IS_VALID_GPIO(config->pin_num_rs), "GPIO RS invalid", NULL);
    I2S_CHECK(config->data_width > 0 && config->data_width <= 16, "Bit width out of range", NULL);
    I2S_CHECK(0 == (config->data_width % 8), "Bit width must be a multiple of 8", NULL);
    uint64_t pin_mask = 0;
    for (size_t i = 0; i < config->data_width; i++) {
        uint64_t mask = 1ULL << config->pin_data_num[i];
        I2S_CHECK(!(pin_mask & mask), "Data bus GPIO has a duplicate", NULL);
        I2S_CHECK(GPIO_IS_VALID_GPIO(config->pin_data_num[i]), "Data bus gpio invalid", NULL);
        pin_mask |= mask;
    }

    i2s_lcd_driver_t *i2s_lcd_drv = (i2s_lcd_driver_t *)heap_caps_malloc(sizeof(i2s_lcd_driver_t), MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
    I2S_CHECK(NULL != i2s_lcd_drv, "Error malloc handle of i2s dma driver", NULL);

    esp_err_t ret = i2s_dma_init(i2s_lcd_drv, config);
    
    if(ESP_OK != ret) {
        ESP_LOGE(TAG,"%s:%d (%s):%s", __FILE__, __LINE__, __FUNCTION__, "i2s dma driver initialize failed");
        heap_caps_free(i2s_lcd_drv);
        return NULL;
    }

    i2s_lcd_drv->mutex = xSemaphoreCreateMutex();
    if (i2s_lcd_drv->mutex == NULL) {
        ESP_LOGE(TAG, "%s:%d (%s):%s", __FILE__, __LINE__, __FUNCTION__, "dma create mutex failed");
        i2s_dma_deinit(i2s_lcd_drv);
        heap_caps_free(i2s_lcd_drv);
        return NULL;
    }

    if (config->pin_num_cs >= 0) {
        gpio_pad_select_gpio(config->pin_num_cs);
        gpio_set_direction(config->pin_num_cs, GPIO_MODE_OUTPUT);
        gpio_set_level(config->pin_num_cs, 0);
    }

    gpio_pad_select_gpio(config->pin_num_rs);
    gpio_set_direction(config->pin_num_rs, GPIO_MODE_OUTPUT);
    //i2s_lcd_drv->rs_io_num = config->pin_num_rs;
    
    //xQueueSend(i2s_lcd_drv->i2s_dma_obj->dma.event_queue, &x, 0);
    return (i2s_lcd_handle_t)i2s_lcd_drv;
}

/**
 * @brief Deinit i2s dma driver. 
 * 
 * @param handle i2s dma driver handle to deinitialize
 * 
 * @return
 *      - ESP_OK on success
 *      - ESP_ERR_INVALID_ARG handle is invalid
 */
esp_err_t i2s_lcd_driver_deinit(i2s_lcd_handle_t handle)
{
    i2s_lcd_driver_t *i2s_lcd_drv = (i2s_lcd_driver_t *)handle;
    I2S_CHECK(NULL != i2s_lcd_drv, "handle pointer invalid", ESP_ERR_INVALID_ARG);
    i2s_dma_deinit(i2s_lcd_drv);
    vSemaphoreDelete(i2s_lcd_drv->mutex);
    heap_caps_free(handle);
    return ESP_OK;
}

void i2s_lcd_write_data(i2s_lcd_handle_t handle, uint8_t *data, size_t len)
{
    int event  = 0;

    i2s_lcd_driver_t * drv = (i2s_lcd_driver_t *)handle;

    i2s_dma_obj_t* i2s_dma_obj = drv->i2s_dma_obj;
    

    
    if (dma_init_desc(&i2s_dma_obj->dma, data, len) != ESP_OK)
    {
        ESP_LOGE(TAG, "wrong len!");
        return;
    }
    // Start signal
    lcd_i2s_start(i2s_dma_obj->i2s, ((uint32_t)&i2s_dma_obj->dma.descriptor[0]) & 0xfffff);   


    xQueueReceive(i2s_dma_obj->dma.event_queue, (void *)&event, portMAX_DELAY);

   
}

/**
 * @brief acquire a lock
 * 
 * @param handle  Handle of i2s dma driver
 * 
 * @return Always return ESP_OK
 */
esp_err_t i2s_lcd_acquire(i2s_lcd_handle_t handle)
{
    i2s_lcd_driver_t *i2s_lcd_drv = (i2s_lcd_driver_t *)handle;
    I2S_CHECK(NULL != i2s_lcd_drv, "handle pointer invalid", ESP_ERR_INVALID_ARG);
    BaseType_t ret = xSemaphoreTake(i2s_lcd_drv->mutex, portMAX_DELAY);
    I2S_CHECK(pdTRUE == ret, "Take semaphore failed", ESP_FAIL);
    return ESP_OK;
}


/**
 * @brief release a lock
 * 
 * @param handle  Handle of i2s dma driver
 * 
 * @return Always return ESP_OK
 */
esp_err_t i2s_lcd_release(i2s_lcd_handle_t handle)
{
    i2s_lcd_driver_t *i2s_lcd_drv = (i2s_lcd_driver_t *)handle;
    I2S_CHECK(NULL != i2s_lcd_drv, "handle pointer invalid", ESP_ERR_INVALID_ARG);
    BaseType_t ret = xSemaphoreGive(i2s_lcd_drv->mutex);
    I2S_CHECK(pdTRUE == ret, "Give semaphore failed", ESP_FAIL);
    return ESP_OK;
}



/**********************
 *  STATIC FUNCTIONS
 **********************/

/**
 * @brief fires after sending the last node "eof"
 * @param arg : void pointer->points to an i2s_dma_obj struct
 */
static void IRAM_ATTR i2s_isr(void *arg)
{
    BaseType_t HPTaskAwoken = pdFALSE;
    i2s_dev_t *i2s = ((i2s_dma_obj_t*)arg)->i2s;

    typeof(i2s->int_st) status = i2s->int_st;
    i2s->int_clr.val = status.val;
    if (status.val == 0) {
        return;
    }

    if (status.out_eof) {
        xQueueSendFromISR(((i2s_dma_obj_t*)arg)->dma.event_queue, (void*)&status.val, &HPTaskAwoken);
 
    }

    

}



/**
 * @brief 
 * 
 * @param drv 
 * @param config 
 * @return esp_err_t 
 */
static esp_err_t i2s_dma_init(i2s_lcd_driver_t *drv, const i2s_lcd_config_t *config)
{
    esp_err_t ret = ESP_OK;

    i2s_dma_obj_t *i2s_dma_obj = (i2s_dma_obj_t *)heap_caps_calloc(1, sizeof(i2s_dma_obj_t), MALLOC_CAP_DMA);
    if (i2s_dma_obj == NULL) {
        ESP_LOGE(TAG, "lcd_cam object malloc error");
        return ESP_ERR_NO_MEM;
    }

    drv->i2s_dma_obj = i2s_dma_obj;

    if (I2S_NUM_0 == config->i2s_port) {
        i2s_dma_obj->i2s = &I2S0;
        periph_module_enable(PERIPH_I2S0_MODULE);
    } else {
        ESP_LOGE(TAG, "Designated I2S peripheral not found");
    }

    ret |= i2s_reg_config(i2s_dma_obj->i2s, config->data_width, config->clk_freq);

    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "lcd_cam config fail!");
        i2s_dma_deinit(drv);
        return ESP_FAIL;
    }

    ret |= lcd_set_pin(config);
    ret |= dma_init(&i2s_dma_obj->dma, config->max_buffer_size);

    if (ret != ESP_OK) {
        i2s_dma_deinit(drv);
        return ESP_FAIL;
    }
    // i2s interrupt init
    // flags: specifies the priority and ISR memory location
    ret |= esp_intr_alloc(ETS_I2S0_INTR_SOURCE, ESP_INTR_FLAG_LOWMED | ESP_INTR_FLAG_IRAM, i2s_isr, i2s_dma_obj, &i2s_dma_obj->i2s_intr_handle);

    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "lcd_cam intr alloc fail!");
        i2s_dma_deinit(drv);
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "dma init ok");

    return ESP_OK;
}

static esp_err_t i2s_dma_deinit(i2s_lcd_driver_t *drv)
{
    if (!drv->i2s_dma_obj) {
        return ESP_FAIL;
    }

    if (drv->i2s_dma_obj->dma.event_queue) {
        vQueueDelete(drv->i2s_dma_obj->dma.event_queue);
    }

    if (drv->i2s_dma_obj->dma.descriptor) {
        heap_caps_free(drv->i2s_dma_obj->dma.descriptor);
    }

    if (drv->i2s_dma_obj->i2s_intr_handle) {
        esp_intr_free(drv->i2s_dma_obj->i2s_intr_handle);
    }

    heap_caps_free(drv->i2s_dma_obj);
    drv->i2s_dma_obj = NULL;
    return ESP_OK;
}

static void lcd_i2s_start(i2s_dev_t *i2s, uint32_t addr)
{
    while (!i2s->state.tx_idle);
    i2s->conf.tx_reset = 1;
    i2s->conf.tx_reset = 0;
    i2s->conf.tx_fifo_reset = 1;
    i2s->conf.tx_fifo_reset = 0;
    i2s->out_link.addr = addr;
    i2s->out_link.start = 1;
    ets_delay_us(1);
    i2s->conf.tx_start = 1;
}


/**
 * @brief sets the I2S module mode(normal, dma, cam), frequency, data format, I2S fifo
 * 
 * @param i2s hardware register struct pointer
 * @param data_width 8 or 16 or 24
 * @param clk_freq in hz
 * @return esp_err_t 
 */
static esp_err_t i2s_reg_config(i2s_dev_t *i2s, uint16_t data_width, uint32_t clk_freq)
{
    // Configure the clock
    i2s->clkm_conf.clkm_div_num = 2; // 160MHz / 2 = 80MHz
    i2s->clkm_conf.clkm_div_b = 0;
    i2s->clkm_conf.clkm_div_a = 0;
    i2s->clkm_conf.clk_sel = 2;
    i2s->clkm_conf.clk_en = 1;

    i2s->conf.val = 0;
    i2s->fifo_conf.val = 0;
    i2s->fifo_conf.dscr_en = 1;

    i2s->lc_conf.ahbm_fifo_rst = 1;
    i2s->lc_conf.ahbm_fifo_rst = 0;
    i2s->lc_conf.ahbm_rst = 1;
    i2s->lc_conf.ahbm_rst = 0;
    i2s->lc_conf.check_owner = 0;

    i2s->timing.val = 0;

    i2s->int_ena.val = 0;   // clear all interrupts
    i2s->int_clr.val = ~0;

    i2s->conf2.lcd_en = 1;

    // Configure sampling rate
    i2s->sample_rate_conf.tx_bck_div_num = 40000000 / clk_freq; // Fws = Fbck / 2
    // Configuration data format
    i2s->sample_rate_conf.tx_bits_mod = data_width;

    i2s->conf.tx_right_first = 1;
    i2s->conf.tx_msb_right = 1;
    i2s->conf.tx_dma_equal = 1;

    i2s->conf1.tx_pcm_bypass = 1;
    i2s->conf1.tx_stop_en = 1;

    i2s->conf2.lcd_en = 1;

    i2s->conf_chan.tx_chan_mod = 1;

    i2s->fifo_conf.tx_data_num = 32;            // 

    i2s->lc_conf.out_rst  = 1;
    i2s->lc_conf.out_rst  = 0;

    i2s->int_ena.out_eof = 1;    // enable interrupt out eof enable


    return ESP_OK;
}

static esp_err_t lcd_set_pin(const i2s_lcd_config_t *config)
{
    PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[config->pin_num_wr], PIN_FUNC_GPIO);
    gpio_set_direction(config->pin_num_wr, GPIO_MODE_OUTPUT);
    gpio_set_pull_mode(config->pin_num_wr, GPIO_FLOATING);
    gpio_matrix_out(config->pin_num_wr, I2S0O_WS_OUT_IDX, true, false);

    for (int i = 0; i < config->data_width; i++) {
        PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[config->pin_data_num[i]], PIN_FUNC_GPIO);
        gpio_set_direction(config->pin_data_num[i], GPIO_MODE_OUTPUT);
        gpio_set_pull_mode(config->pin_data_num[i], GPIO_FLOATING);
        // High bit aligned, OUT23 is always the highest bit
        gpio_matrix_out(config->pin_data_num[i], I2S0O_DATA_OUT0_IDX + (LCD_DATA_MAX_WIDTH - config->data_width) + i, false, false);
    }

    return ESP_OK;
}

/**
 * @brief initialzation of dma descriptors
 * 
 * @param i2s_dma_obj 
 */
static esp_err_t dma_init_desc(dma_obj_t *dma, uint8_t* buff, size_t len)
{
    // Generate a data DMA linked list
    uint8_t num_nodes = len / dma->node_buffer_size;

    if (len <= 0 || num_nodes > dma->node_cnt) 
    {
        return ESP_FAIL; 
    }

    int8_t i;
    for (i = 0; i < num_nodes; i++) 
    {
        dma->descriptor[i].size = dma->node_buffer_size;
        dma->descriptor[i].length = dma->node_buffer_size;
        dma->descriptor[i].buf = buff + (dma->node_buffer_size * i);
        dma->descriptor[i].eof = 0;
        dma->descriptor[i].empty = (uint32_t)&dma->descriptor[i + 1];
    }
    

    uint16_t x = len % dma->node_buffer_size;

    
    if(x != 0) //if the last node doesn't have a full node_buffer_size
    {
        dma->descriptor[num_nodes].size = x;
        dma->descriptor[num_nodes].length = x;
        dma->descriptor[num_nodes].buf = buff + (dma->node_buffer_size * num_nodes);
        dma->descriptor[num_nodes].eof = 1;
        dma->descriptor[num_nodes].empty = (void *)NULL;
    }
    else //if the last node has a full node_buffer_size
    {
        dma->descriptor[num_nodes-1].eof = 1;
        dma->descriptor[num_nodes-1].empty = (void *)NULL;
    }

    return ESP_OK;
}

/**
 * @brief 
 * init function of the i2s dma controller
 * -allocate DMA discriptors
 * @param i2s_dma_obj 
 * @param max_dma_buffer_size 
 * @return esp_err_t 
 */
static esp_err_t dma_init(dma_obj_t *dma, uint32_t max_dma_buffer_size)
{
    //int cnt = 0;
    if(max_dma_buffer_size < DMA_NODE_BUFFER_MAX_SIZE)
    {
        dma->node_buffer_size = max_dma_buffer_size;
        dma->node_cnt = 1;
    }
    else
    {
        dma->node_buffer_size = DMA_NODE_BUFFER_MAX_SIZE;
        dma->node_cnt = ceil((float)max_dma_buffer_size / (float)(DMA_NODE_BUFFER_MAX_SIZE)); // Number of DMA nodes
    }

    ESP_LOGI(TAG, "lcd_buffer_size: %d, lcd_dma_size: %d, lcd_dma_node_cnt: %d", dma->node_buffer_size, DMA_NODE_BUFFER_MAX_SIZE, dma->node_cnt);

    dma->descriptor = (lldesc_t *)heap_caps_malloc(dma->node_cnt * sizeof(lldesc_t), MALLOC_CAP_DMA | MALLOC_CAP_8BIT);
    if(dma->descriptor == NULL)
    {
        ESP_LOGE(TAG, "descriptor mem alloc fail!");
        //i2s_dma_deinit(drv);
        return ESP_ERR_NO_MEM;
    }

    dma->event_queue = xQueueCreate(1, sizeof(int));
    if (dma->event_queue == NULL) {
        ESP_LOGE(TAG, "dma config fail!");
        //i2s_dma_deinit(drv);
        return ESP_FAIL;
    }
    return ESP_OK;
}
