    // Copyright 2020 Espressif Systems (Shanghai) Co. Ltd.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "../hal_err.h"

#include "ssd1963.h"
#include "ssd1963_cfg.h"
#include "lvgl.h"
#include <stdio.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define TAG "lcd ssd1963"




#define LCD_CHECK(a, str, ret)




static scr_handle_t g_lcd_handle;

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void ssd1963_init_reg(void);
static inline void SSD1963_WRITE_REG(uint16_t cmd, uint16_t data);
static void ssd1963_set_rotation(scr_dir_t dir);
static void ssd1963_set_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);

/**********************
 *  GLOBAL FUNCTIONS
 **********************/
/**
 * @brief   device initialization
 */
void ssd1963_init()
{
    //Reset the display
    #if GPIO_PIN_EN >= 0
        mcal_gpio_set_direction(GPIO_PORT_EN, GPIO_PIN_EN, GPIO_MODE_OUTPUT);
        mcal_gpio_set_level(GPIO_PORT_EN, GPIO_PIN_EN, 0);
        vTaskDelay(100 / portTICK_RATE_MS);//todo
        mcal_gpio_set_level(GPIO_PORT_EN, GPIO_PIN_EN, 1);
        vTaskDelay(100 / portTICK_RATE_MS);//todo
    #endif
    
    g_lcd_handle.original_width = SSD_HOR_RESOLUTION;
    g_lcd_handle.original_height = SSD_VER_RESOLUTION;
    //todo: delete offset
    g_lcd_handle.offset_hor = 0;
    g_lcd_handle.offset_ver = 0;
    // mcal interface init
	mcal_comm8080_init();
    // component init
    ssd1963_init_reg();

    #if GPIO_PIN_BL >= 0
        mcal_gpio_set_direction(GPIO_PORT_BL, GPIO_PIN_BL, GPIO_MODE_OUTPUT);
        mcal_gpio_set_level(GPIO_PORT_BL, GPIO_PIN_BL, 0x1);

    #endif

    ssd1963_set_rotation(SSD_ORIENTATION);


}


void ssd1963_flush(lv_disp_drv_t * drv, const lv_area_t * area, lv_color_t * color_map)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);



    //lcd_interface_acquire();

    ssd1963_set_window(area->x1, area->y1, area->x2, area->y2);
    mcal_comm8080_write((uint8_t *)color_map, w * SSD_BPP / 8 * h);
    //lcd_interface_release();
}

esp_err_t lcd_ssd1963_draw_bitmap(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t *bitmap)
{
    LCD_CHECK((x + w <= g_lcd_handle.width) && (y + h <= g_lcd_handle.height), "The set coordinates exceed the screen size", ESP_ERR_INVALID_ARG);
    esp_err_t ret = ESP_OK;
    uint8_t *p = (uint8_t *)bitmap;

    //LCD_IFACE_ACQUIRE();
    ssd1963_set_window(x, y, x + w - 1, y + h - 1);
    if (ESP_OK != ret) {
        return ESP_FAIL;
    }

    mcal_comm8080_write(p, w * SSD_BPP / 8 * h);
    //LCD_IFACE_RELEASE();
    //LCD_CHECK(ESP_OK == ret, "Draw bitmap failed", ESP_FAIL);
    return ESP_OK;
}



/**********************
 *  STATIC FUNCTIONS
 **********************/

/**
 * @brief Set screen direction of rotation
 *
 * @param dir Pointer to a scr_dir_t structure.
 * 
 * @return
 *     - HAL_OK Success
 *     - HAL_FAIL Fail
 */
static void ssd1963_set_rotation(scr_dir_t dir)
{
    uint8_t reg_data = 0;
    reg_data |= MADCTL_RGB;
    if (SCR_DIR_MAX < dir) {
        dir >>= 5;
    }
    LCD_CHECK(dir < 8, "Unsupport rotate direction", HAL_ERR_INVALID_ARG);
    switch (dir) {
    case SCR_DIR_LRTB:
        g_lcd_handle.width = g_lcd_handle.original_width;
        g_lcd_handle.height = g_lcd_handle.original_height;
        break;
    case SCR_DIR_LRBT:
        reg_data |= MADCTL_MY;
        g_lcd_handle.width = g_lcd_handle.original_width;
        g_lcd_handle.height = g_lcd_handle.original_height;
        break;
    case SCR_DIR_RLTB:
        reg_data |= MADCTL_MX;
        g_lcd_handle.width = g_lcd_handle.original_width;
        g_lcd_handle.height = g_lcd_handle.original_height;
        break;
    case SCR_DIR_RLBT:
        reg_data |= MADCTL_MX | MADCTL_MY;
        g_lcd_handle.width = g_lcd_handle.original_width;
        g_lcd_handle.height = g_lcd_handle.original_height;
        break;

    case SCR_DIR_TBLR:
        reg_data |= MADCTL_MV;
        g_lcd_handle.width = g_lcd_handle.original_height;
        g_lcd_handle.height = g_lcd_handle.original_width;
        break;
    case SCR_DIR_BTLR:
        reg_data |= MADCTL_MY | MADCTL_MV;
        g_lcd_handle.width = g_lcd_handle.original_height;
        g_lcd_handle.height = g_lcd_handle.original_width;
        break;
    case SCR_DIR_TBRL:
        reg_data |= MADCTL_MX | MADCTL_MV;
        g_lcd_handle.width = g_lcd_handle.original_height;
        g_lcd_handle.height = g_lcd_handle.original_width;
        break;
    case SCR_DIR_BTRL:
        reg_data |= MADCTL_MX | MADCTL_MY | MADCTL_MV;
        g_lcd_handle.width = g_lcd_handle.original_height;
        g_lcd_handle.height = g_lcd_handle.original_width;
        break;
    default: break;
    }
    ESP_LOGI(TAG, "MADCTL=0x%x", reg_data);
    SSD1963_WRITE_REG(SSD1963_MADCTL, reg_data);
    g_lcd_handle.dir = dir;
}

static void scr_utility_apply_offset(const scr_handle_t *lcd_handle, uint16_t res_hor, uint16_t res_ver, uint16_t *x0, uint16_t *y0, uint16_t *x1, uint16_t *y1)
{
    scr_dir_t dir = lcd_handle->dir;
    if (SCR_DIR_MAX < dir) {
        dir >>= 5;
    }
    uint16_t xoffset=0, yoffset=0;
    switch (dir) {
        case SCR_DIR_LRTB:
            xoffset = lcd_handle->offset_hor;
            yoffset = lcd_handle->offset_ver;
            break;
        case SCR_DIR_LRBT:
            xoffset = lcd_handle->offset_hor;
            yoffset = res_ver - lcd_handle->offset_ver - lcd_handle->original_height;
            break;
        case SCR_DIR_RLTB:
            xoffset += res_hor - lcd_handle->offset_hor - lcd_handle->original_width;
            yoffset += lcd_handle->offset_ver;
            break;
        case SCR_DIR_RLBT:
            xoffset = res_hor - lcd_handle->offset_hor - lcd_handle->original_width;
            yoffset = res_ver - lcd_handle->offset_ver - lcd_handle->original_height;
            break;

        case SCR_DIR_TBLR:
            xoffset = lcd_handle->offset_ver;
            yoffset = lcd_handle->offset_hor;
            break;
        case SCR_DIR_BTLR:
            yoffset = lcd_handle->offset_hor;
            xoffset = res_ver - lcd_handle->offset_ver - lcd_handle->original_height;
            break;
        case SCR_DIR_TBRL:
            yoffset += res_hor - lcd_handle->offset_hor - lcd_handle->original_width;
            xoffset += lcd_handle->offset_ver;
            break;
        case SCR_DIR_BTRL:
            yoffset = res_hor - lcd_handle->offset_hor - lcd_handle->original_width;
            xoffset = res_ver - lcd_handle->offset_ver - lcd_handle->original_height;
            break;
        default: break;
    }
    ESP_LOGD(TAG, "dir=%d, offset=(%d, %d)", dir, xoffset, yoffset);
    *x0 += xoffset;
    *x1 += xoffset;
    *y0 += yoffset;
    *y1 += yoffset;
}

/**
 * @brief Set screen window
 *
 * @param x0 Starting point in X direction
 * @param y0 Starting point in Y direction
 * @param x1 End point in X direction
 * @param y1 End point in Y direction
 * 
 * @return
 *      - HAL_OK on success
 *      - HAL_FAIL Failed
 */
static void ssd1963_set_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{

	LCD_CHECK((x1 < g_lcd_handle.width) && (y1 < g_lcd_handle.height), "The set coordinates exceed the screen size", HAL_ERR_INVALID_ARG);
    LCD_CHECK((x0 <= x1) && (y0 <= y1), "Window coordinates invalid", HAL_ERR_INVALID_ARG);


    scr_utility_apply_offset(&g_lcd_handle, SSD_HOR_RESOLUTION, SSD_VER_RESOLUTION, &x0, &y0, &x1, &y1);

    mcal_comm8080_write_cmd(SSD1963_CASET);
    mcal_comm8080_write_data(x0>>8);
    mcal_comm8080_write_data(x0&0XFF);
    mcal_comm8080_write_data(x1>>8);
    mcal_comm8080_write_data(x1&0XFF);
    mcal_comm8080_write_cmd(SSD1963_RASET);
    mcal_comm8080_write_data(y0>>8);
    mcal_comm8080_write_data(y0&0XFF);
    mcal_comm8080_write_data(y1>>8);
    mcal_comm8080_write_data(y1&0XFF);
    mcal_comm8080_write_cmd(SSD1963_RAMWR);
}



static inline void SSD1963_WRITE_REG(uint16_t cmd, uint16_t data)
{
    mcal_comm8080_write_cmd(cmd);
    mcal_comm8080_write_data(data);
}

/**
 * init ssd1963 internal registers
 * communication is a command followed by the command paramerters.
 * to configure the SSD1963.
 */
static void ssd1963_init_reg(void)
{
    //reset
	//lcd_write_cmd(0x01);
    //wait
	//vTaskDelay(pdMS_TO_TICKS(100));

	// lcd_write_cmd(0xE2);	
	// lcd_write_data(0x1D);	
	// lcd_write_data(0x02);	 // Divider M = 2, PLL = 300/(M+1) = 100MHz
	// lcd_write_data(0x04);
	
    // Set MN of PLL
    mcal_comm8080_write_cmd(0xE2);		//Set PLL with OSC = 10MHz (hardware),	Multiplier N = 35, 250MHz < VCO < 800MHz = OSC*(N+1), VCO = 300MHz paramter
    mcal_comm8080_write_data(0x23);		//Mulipier M VCO = OSC * (M+1) = 10*35+1 = 360
	mcal_comm8080_write_data(0x02);		//Divider N = 2, PLL = VCO/(N+1) = 120MHz
	mcal_comm8080_write_data(0x54);		//Validate M and N values

	vTaskDelay(pdMS_TO_TICKS(1));
	
	mcal_comm8080_write_cmd(0xE0);		// Start PLL command
	mcal_comm8080_write_data(0x01);		// enable PLL

	vTaskDelay(pdMS_TO_TICKS(10));

	mcal_comm8080_write_cmd(0xE0);		// Start PLL command again
	mcal_comm8080_write_data(0x03);		// now, use PLL output as system clock
	
	vTaskDelay(pdMS_TO_TICKS(12));  
	
	mcal_comm8080_write_cmd(0x01);		// Soft reset
	
	vTaskDelay(pdMS_TO_TICKS(10));
	
	mcal_comm8080_write_cmd(0xE6);		// LCD pixel clock freq 33Mhz -LSHIFT-
	mcal_comm8080_write_data(0x01);       //MSB
	mcal_comm8080_write_data(0x1F);
	mcal_comm8080_write_data(0xFF);       //lSB

	mcal_comm8080_write_cmd(0xB0);		// LCD mode & Resolution
	mcal_comm8080_write_data(0x20);		// LCD config
	mcal_comm8080_write_data(0x0000);		// COMM -> TFT Mode
	mcal_comm8080_write_data((SSD_HOR_RESOLUTION-1)>>8); // horizontal resolution
	mcal_comm8080_write_data(SSD_HOR_RESOLUTION-1);
	mcal_comm8080_write_data((SSD_VER_RESOLUTION-1)>>8);// vertical resolution
	mcal_comm8080_write_data(SSD_VER_RESOLUTION-1);
	mcal_comm8080_write_data(0x00);		//RGB COLOR sequence
	
	mcal_comm8080_write_cmd(0xB4);		//Set horizontal period -front and back porch-
	mcal_comm8080_write_data((SSD_HT-1)>>8);
	mcal_comm8080_write_data(SSD_HT-1);
	mcal_comm8080_write_data(SSD_HPS>>8);
	mcal_comm8080_write_data(SSD_HPS);
	mcal_comm8080_write_data(SSD_HOR_PULSE_WIDTH-1);
	mcal_comm8080_write_data(0x00);
	mcal_comm8080_write_data(0x00);
	mcal_comm8080_write_data(0x00);

	mcal_comm8080_write_cmd(0xB6);		//Set vertical period -front and back porch-
	mcal_comm8080_write_data((SSD_VT-1)>>8);
	mcal_comm8080_write_data(SSD_VT-1);
	mcal_comm8080_write_data(SSD_VPS>>8);
	mcal_comm8080_write_data(SSD_VPS);
	mcal_comm8080_write_data(SSD_VER_FRONT_PORCH-1);
	mcal_comm8080_write_data(0x00);
	mcal_comm8080_write_data(0x00);
	
	mcal_comm8080_write_cmd(0xF0);	// Data interface -PINS & format-
	mcal_comm8080_write_data(0x03);	// 16-bit(565 format) data for 16bpp"bit per pixel""

	mcal_comm8080_write_cmd(0x29);	// Set display ON
	
	mcal_comm8080_write_cmd(0xD0);	// Dynamic Backlight Control
	mcal_comm8080_write_data(0x00);	// disable
	
	// Brightness PWM pin config
	mcal_comm8080_write_cmd(0xBE);	// set the PWM Configuration parameters
	mcal_comm8080_write_data(0x05);	// freq
	mcal_comm8080_write_data(0xFE);	// Duty Cycle
	mcal_comm8080_write_data(0x01);	// config auto/controled en/disable
	mcal_comm8080_write_data(0x00);	// manual brightness -> brightest // 0xD0 disables
	mcal_comm8080_write_data(0x00);	// minimum brightness
	mcal_comm8080_write_data(0x00);	// prescaler

	mcal_comm8080_write_cmd(0xB8);	// GPIO Config
	mcal_comm8080_write_data(0x03);	// Direction & (Host|LCDC)
	mcal_comm8080_write_data(0x01);	// Sleep Mode
	
	mcal_comm8080_write_cmd(0xBA);    // GPIO DATA
	mcal_comm8080_write_data(0X01);	//GPIO[1:0]=01
}

void ssd1963_set_gpio0_output(uint8_t data)
{
    mcal_comm8080_write_cmd(0xBA);    // GPIO DATA
	mcal_comm8080_write_data(data);   // GPIO[1:0]=01
}
