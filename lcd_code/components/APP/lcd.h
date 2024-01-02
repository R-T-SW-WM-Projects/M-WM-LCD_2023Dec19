/******************************************************************************************************************************
 File Name      : lcd.h
 Description    : This file as Header for (lcd)
 Author         : Ahmed Yasser
 Tester         : Ahmed Yasser
 Device(s)      : lcd device
 Creation Date  : 19/12/2023
 Testing Date   :
 @COPYRIGHT 2016 El-ARABY Research and development center.
 all rights reserved
*********************************************************************************************************************************/

#ifndef  LCD_H_
#define  LCD_H_

/* Includes */
#include "../../components/lvgl/src/font/lv_symbol_def.h"
#include "lcd_user.h"
#include "../../components/lvgl_porting/lv_port_disp.h"
#include "../../components/lvgl_porting/lv_port_indev.h"
#include "../../components/sw_pressing/sw_pressing.h"
#include "lcd_attachment.h"

#define tbyte uint8_t
//******************************************************************************************** 
/*General Selection*/
typedef enum {
    BLACK =0,
    WHITE,
    RED,
    light_RED,
    dark_RED,
    BLUE,
    YELLOW,
    GRAY,
    GREEN
}t_color;
//******************************************************************************************** 
/*LCD*/
// init (lvgl-touch-ssd1963)
void lcd_init(void);
//******************************************************************************************** 
/*Screen*/
//screenIndex 0~(max_screens-1)
void  screen_set_color(tbyte screenIndex, t_color screenColor);
void  Go_to_screen(tbyte screenIndex);




typedef struct  {
    lv_obj_t* screen;
    const char* label_text;
    lv_align_t align;
    lv_coord_t x_offset;
    lv_coord_t y_offset;
    lv_coord_t width;
    lv_coord_t height;
    uint8_t bg_color;
    uint8_t label_color;
}ButtonParams;

/* API */

/*screen*/

lv_color_t set_color(t_color needed_color);
lv_obj_t* button_init( ButtonParams params);

void label_create(tbyte screenIndex, tbyte textIndex);
void label_set_text(tbyte textIndex, const char* text);
void label_set_color(tbyte textIndex, t_color txt_color);
void label_set_position(tbyte textIndex, lv_coord_t x, lv_coord_t y);
void label_set_font(tbyte textIndex, lv_font_t* font);
void label_set_background(tbyte textIndex, const char* text, lv_coord_t x, lv_coord_t y, uint8_t bg_color, uint8_t txt_color, lv_font_t* font);
void label_remove(tbyte textIndex);

/*==============================================================================================================================*/
/*END*/




#endif 