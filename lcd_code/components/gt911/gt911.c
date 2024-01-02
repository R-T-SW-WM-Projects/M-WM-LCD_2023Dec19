/*
* Copyright © 2021 Sturnus Inc.

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

/*********************
 *     INCLUDES
 *********************/
#include <esp_log.h>
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include <lvgl.h>
#else
#include <lvgl/lvgl.h>
#endif
#include "gt911.h"
#include "gt911_cfg.h"
#include "gt911_const.h"
#include "i2c_manager.h"
#include <stdint.h>
#include <driver/gpio.h>

/*********************
 *      DEFINES
 *********************/
#define TAG "GT911"

static gt911_status_t gt911_status;
// config area from register 0x8047: 0x80fe
#define GOODIX_CONTACT_SIZE 8
#define GOODIX_MAX_CONTACTS 5
#define GT911_CONFIG_SIZE 0xFE - 0x47 + 1
static uint8_t configBuf[GT911_CONFIG_SIZE];

/*********************
 *  STATIC FUNCTIONS
 *********************/
// TODO: handle multibyte read and refactor to just one read transaction
static esp_err_t gt911_i2c_read(uint16_t register_addr, uint8_t *data_buf, uint8_t len)
{
    return i2c_manager_read(gt911_I2C_PORT, gt911_status.i2c_dev_addr, register_addr | I2C_REG_16, data_buf, len);
}

static esp_err_t gt911_i2c_write8(uint16_t register_addr, uint8_t data)
{
    uint8_t buffer = data;
    return i2c_manager_write(gt911_I2C_PORT, gt911_status.i2c_dev_addr, register_addr | I2C_REG_16, &buffer, 1);
}

static uint8_t calculateChecksum()
{
    uint8_t checksum = 0;
    for (uint8_t i = 0; i < GT911_CONFIG_SIZE; i++)
    {
        checksum += configBuf[i];
    }
    checksum = (~checksum) + 1;
    return checksum;
}

void gt911_reflashConfig()
{
    uint8_t csum = calculateChecksum();
    gt911_i2c_write8(GT911_CONFIG_CHKSUM, csum);
    gt911_i2c_write8(GT911_CONFIG_FRESH, 1);
}

static void gt911_setResolution(uint16_t _width, uint16_t _height)
{
    configBuf[GT911_X_OUTPUT_MAX_LOW - GT911_CONFIG_START] = _width & 0xff;
    configBuf[GT911_X_OUTPUT_MAX_HIGH - GT911_CONFIG_START] = (_width >> 8) & 0xff;
    configBuf[GT911_Y_OUTPUT_MAX_LOW - GT911_CONFIG_START] = _height & 0xff;
    configBuf[GT911_Y_OUTPUT_MAX_HIGH - GT911_CONFIG_START] = (_height >> 8) & 0xff;

    gt911_i2c_write8(GT911_X_OUTPUT_MAX_LOW, configBuf[GT911_X_OUTPUT_MAX_LOW - GT911_CONFIG_START]);
    gt911_i2c_write8(GT911_X_OUTPUT_MAX_HIGH, configBuf[GT911_X_OUTPUT_MAX_HIGH - GT911_CONFIG_START]);
    gt911_i2c_write8(GT911_Y_OUTPUT_MAX_LOW, configBuf[GT911_Y_OUTPUT_MAX_LOW - GT911_CONFIG_START]);
    gt911_i2c_write8(GT911_Y_OUTPUT_MAX_HIGH, configBuf[GT911_Y_OUTPUT_MAX_HIGH - GT911_CONFIG_START]);
    gt911_reflashConfig();
}

static int16_t readInput(uint8_t *regState)
{
    int touch_num;
    int error;

    error = gt911_i2c_read(GT911_STATUS_REG, regState, GOODIX_CONTACT_SIZE);
    touch_num = regState[0] & 0xF;

    if (error)
    {
        return -2;
    }

    if (!(regState[0] & 0x80))
    {
        return -1;
    }

    return touch_num;
}

/*********************
 *  GLOBAL FUNCTIONS
 *********************/
/**
 * @brief  Initialize for GT911 communication via I2C
 * @param  dev_addr: Device address on communication Bus (I2C slave address of GT911).
 * @retval None
 */
void gt911_init(uint8_t dev_addr)
{
    if (!gt911_status.inited)
    {
        vTaskDelay(1);

        gpio_set_direction(intPin, GPIO_MODE_OUTPUT);
        gpio_set_direction(rstPin, GPIO_MODE_OUTPUT);

        gpio_set_level(intPin, 0);
        gpio_set_level(rstPin, 0);

        /* begin select I2C slave addr */

        /* T2: > 10ms */
        vTaskDelay(11/portTICK_PERIOD_MS);

        /* HIGH: 0x28/0x29 (0x14 7bit), LOW: 0xBA/0xBB (0x5D 7bit) */
        gpio_set_level(intPin, dev_addr == 0x14);

        /* T3: > 100us */
        vTaskDelay(1/portTICK_PERIOD_MS);
        gpio_set_direction(rstPin, GPIO_MODE_INPUT);
        // if (!pinCheck(rstPin, HIGH))
        //   return false;

        /* T4: > 5ms */
        vTaskDelay(5/portTICK_PERIOD_MS);
        gpio_set_level(intPin, 0);
        /* end select I2C slave addr */

        /* T5: 50ms */
        vTaskDelay(51);
        gpio_set_direction(intPin, GPIO_MODE_INPUT); // INT pin has no pullups so simple set to floating input

        gt911_status.i2c_dev_addr = dev_addr;
        uint8_t data_buf;
        esp_err_t ret;

        ESP_LOGI(TAG, "Checking for GT911 Touch Controller");
        if ((ret = gt911_i2c_read(GT911_PRODUCT_ID1, &data_buf, 1) != ESP_OK))
        {
            ESP_LOGE(TAG, "Error reading from device: %s",
                     esp_err_to_name(ret)); // Only show error the first time
            return;
        }

        // Read 4 bytes for Product ID in ASCII
        for (int i = 0; i < GT911_PRODUCT_ID_LEN; i++)
        {
            gt911_i2c_read((GT911_PRODUCT_ID1 + i), (uint8_t *)&(gt911_status.product_id[i]), 1);
        }
        ESP_LOGI(TAG, "\tProduct ID: %s", gt911_status.product_id);

        gt911_i2c_read(GT911_VENDOR_ID, &data_buf, 1);
        ESP_LOGI(TAG, "\tVendor ID: 0x%02x", data_buf);


        gt911_i2c_write8(GT911_COMMAND, 0);

        gt911_i2c_read(GT911_CONFIG_START, configBuf, GT911_CONFIG_SIZE);


        uint8_t csum = calculateChecksum();
        uint8_t config_csum = 0;
        gt911_i2c_read(GT911_CONFIG_CHKSUM, &config_csum, 1);

        if (csum != config_csum)
        {
            ESP_LOGI(TAG, "Config checksum error");
        }
        else
        {
            ESP_LOGI(TAG, "Config checksum OK");
        }

        ESP_LOGW(TAG, "x_LOW:0x%x", configBuf[GT911_X_OUTPUT_MAX_LOW - GT911_CONFIG_START]);
        ESP_LOGW(TAG, "x_HIGH:0x%x", configBuf[GT911_X_OUTPUT_MAX_HIGH - GT911_CONFIG_START]);
        ESP_LOGW(TAG, "Y_LOW:0x%x", configBuf[GT911_Y_OUTPUT_MAX_LOW - GT911_CONFIG_START]);
        ESP_LOGW(TAG, "Y_HIGH:0x%x", configBuf[GT911_Y_OUTPUT_MAX_HIGH - GT911_CONFIG_START]);

        gt911_i2c_write8(GT911_COMMAND, 0);
        gt911_setResolution(LV_HOR_RES_MAX, LV_VER_RES_MAX);
        struct GTInfo
        {
            // 0x8140-0x814A
            char productId[4];
            uint16_t fwId;
            uint16_t xResolution;
            uint16_t yResolution;
            uint8_t vendorId;
        } info;
        gt911_i2c_read(GT911_PRODUCT_ID1, (uint8_t *)&info, sizeof(info));
        gt911_status.max_x_coord = info.xResolution;
        gt911_status.max_y_coord = info.yResolution;
        ESP_LOGI(TAG, "\tX Resolution: %d", gt911_status.max_x_coord);
        ESP_LOGI(TAG, "\tY Resolution: %d", gt911_status.max_y_coord);
        gt911_status.inited = true;
    }
}


/**
 * @brief  Get the touch screen X and Y positions values. Ignores multi touch
 * @param  drv:
 * @param  data: Store data here
 * @retval Always false
 */
bool gt911_read(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
    static uint16_t last_x, last_y;

    uint8_t rawdata[GOODIX_CONTACT_SIZE]; // points buffer

    int8_t contacts = readInput(rawdata);

    data->state = LV_INDEV_STATE_REL;
    if (contacts < 0)
    {
        return false;
    }

    if (contacts > 0)
    {
        last_x = ((uint16_t)rawdata[3] << 8) + rawdata[2];
        last_y = ((uint16_t)rawdata[5] << 8) + rawdata[4];
#if GT911_INVERT_X
        last_x = gt911_status.max_x_coord - last_x;
#endif
#if GT911_INVERT_Y
        last_y = gt911_status.max_y_coord - last_y;
#endif
#if GT911_SWAPXY
        int16_t swap_buf = last_x;
        last_x = last_y;
        last_y = swap_buf;
#endif
        data->point.x = last_x;
        data->point.y = last_y;
        data->state = LV_INDEV_STATE_PR;
        ESP_LOGI(TAG, "X=%u Y=%u", data->point.x, data->point.y);
    }
    gt911_i2c_write8(GT911_STATUS_REG, 0);

    return false;
}
