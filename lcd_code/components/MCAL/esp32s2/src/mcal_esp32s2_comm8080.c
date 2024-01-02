#include <stdio.h>
#include <stdlib.h>
#include "stdint.h"

#include "mcal_esp32s2.h"  //mcal header
#include "ssd1963_cfg.h"
#include "i2s_lcd.h"
#include "driver/i2s.h"
#include "i2s_lcd_types.h"




static i2s_lcd_handle_t driver;

#define I2S_LCD I2S_NUM_0
#define DMA_MAX_BUFF (LV_DRAW_BUFF_SIZE * (SSD_BPP/8))

/**********************
 * GLOBAL FUNCTION
 **********************/
void mcal_comm8080_init()
{
    //init I2S_NUM_1
     i2s_lcd_config_t config = {
		.data_width = SSD_BIT_WIDTH,
	    .pin_data_num = {
	      GPIO_LCD_D00, GPIO_LCD_D01, GPIO_LCD_D02, GPIO_LCD_D03,
	      GPIO_LCD_D04, GPIO_LCD_D05, GPIO_LCD_D06, GPIO_LCD_D07,
	      GPIO_LCD_D08, GPIO_LCD_D09, GPIO_LCD_D10, GPIO_LCD_D11,
	      GPIO_LCD_D12, GPIO_LCD_D13, GPIO_LCD_D14, GPIO_LCD_D15,
	    },
	    .pin_num_cs = GPIO_PIN_CS,
	    .pin_num_wr = GPIO_PIN_WR,
		.pin_num_rs = GPIO_PIN_RS, // DC-> data or command / rs -> register select
	    .clk_freq = SSD_COMM_CLK_HZ,
	    .i2s_port = I2S_LCD,
		.max_buffer_size = DMA_MAX_BUFF,
	    };

    driver = i2s_lcd_driver_init(&config);
}

/**
 * @brief Write a data to LCD
 * 
 * @param data Data to write
 */
// todo: return fail or ok
void mcal_comm8080_write_data(uint16_t data)
{
    i2s_lcd_write_data(driver, (uint8_t *)&data, 2);
}

/**
 * @brief Write a command to LCD
 * 
 * @param cmd command to write
 */
void mcal_comm8080_write_cmd(uint16_t cmd)
{
    gpio_set_level(GPIO_PIN_RS, 0);
    i2s_lcd_write_data(driver, (uint8_t *)&cmd, 2);
    gpio_set_level(GPIO_PIN_RS, 1);
}

/**
 * @brief Write block data to LCD
 * 
 * @param data Pointer of data
 * @param length length of data
 */
void mcal_comm8080_write(const uint8_t *data, uint32_t length)
{
	i2s_lcd_write_data(driver, (uint8_t*)data, length);
}



/**
 * @brief release a lock
 * 
 * @param handle  Handle of i2s lcd driver
 * 
 * @return Always return HAL_OK
 */
esp_err_t mcal_comm8080_release(void)
{
    return i2s_lcd_release(driver);
}

esp_err_t mcal_comm8080_acquire(void)
{
	return i2s_lcd_acquire(driver);
}
