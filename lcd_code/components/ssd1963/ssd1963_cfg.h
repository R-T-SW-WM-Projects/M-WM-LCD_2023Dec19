#ifndef __SSD1963_CFG_H
#define __SSD1963_CFG_H

/*********************
 *     INCLUDE
 *********************/
#include "ssd1963_const.h"
#include "../../MCAL/mcal.h"

/*********************
 *    USER DEFINE
 *********************/

//TODO:ORIANTATION VALUES NEED TEST


#define SSD_COMM_CLK_HZ    20000000
#define SSD_ORIENTATION  SSD_ORIENTATION_LANDSCAPE

#define GPIO_PIN_BL     (GPIO_PIN_NC)    //Backlight
#define GPIO_PORT_BL    (GPIO_NC)     
#define GPIO_PIN_CS     (GPIO_PIN_NC)    //Chip select
#define GPIO_PORT_CS    (GPIO_NC)
#define GPIO_PIN_EN     (GPIO_PIN_NC)    //RESET
#define GPIO_PORT_EN    (GPIO_NC)
#define GPIO_PIN_RS     (PIN_20)    //DATA command
#define GPIO_PORT_RS    (GPIO_NC)
#define GPIO_PIN_WR     (PIN_3)    //write clock
#define GPIO_PORT_WR    (GPIO_NC)

#define SSD_BIT_WIDTH   (16)
//LCD RGB Protocol paramaters
#define SSD_HOR_PULSE_WIDTH		2		//
#define SSD_HOR_BACK_PORCH		42		//
#define SSD_HOR_FRONT_PORCH		2		//

#define SSD_VER_PULSE_WIDTH		10		//
#define SSD_VER_BACK_PORCH		2		//
#define SSD_VER_FRONT_PORCH		2		//


#define SSD_BPP  16        //Bit per pixel


#if SSD_BIT_WIDTH == 8
//todo: modify port
#define GPIO_LCD_D00    (PIN_26)
#define GPIO_LCD_D01    (PIN_2)
#define GPIO_LCD_D02    (PIN_13)
#define GPIO_LCD_D03    (PIN_19)
#define GPIO_LCD_D04    (PIN_4)
#define GPIO_LCD_D05    (PIN_5)
#define GPIO_LCD_D06    (PIN_21)
#define GPIO_LCD_D07    (PIN_22)
#define GPIO_PORT_LSB   (GPIO_NC)

#elif SSD_BIT_WIDTH == (16)


//todo: modify port
#define GPIO_PORT_LSB   (GPIO_NC)
#define GPIO_PORT_MSB   (GPIO_NC)


#define GPIO_LCD_D00    (PIN_19)
#define GPIO_LCD_D01    (PIN_8)
#define GPIO_LCD_D02    (PIN_18)
#define GPIO_LCD_D03    (PIN_17)
#define GPIO_LCD_D04    (PIN_16)
#define GPIO_LCD_D05    (PIN_9)
#define GPIO_LCD_D06    (PIN_10)
#define GPIO_LCD_D07    (PIN_11)

#define GPIO_LCD_D08    (PIN_12)
#define GPIO_LCD_D09    (PIN_13)
#define GPIO_LCD_D10    (PIN_14)
#define GPIO_LCD_D11    (PIN_21)
#define GPIO_LCD_D12    (PIN_33)
#define GPIO_LCD_D13    (PIN_34)
#define GPIO_LCD_D14    (PIN_35)
#define GPIO_LCD_D15    (PIN_36)

#endif


#endif