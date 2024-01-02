/******************************************************************************************************************************
 File Name      : LCD.C
 Description    : This file as Source Code for (LCD)
 Author         : Ahmed Yasser
 Tester         : Ahmed Yasser
 Device(s)      : lcd device
 Creation Date  : 19/12/2023
 Testing Date   :
 @COPYRIGHT 2016 El-ARABY Research and development center.
 all rights reserved
 *********************************************************************************************************************************/
 /* Includes */
#include "lvgl/lvgl.h"
#include "lcd.h"
#include "ui_helpers.h"
#include <stdlib.h>
/*==============================================================================================================================*/
/* static Variables */
 TextParams text_params[max_text];
/*==============================================================================================================================*/
/*Global variables and functions*
* 
 ***********************************************************************************************************************/


/*functions */

void lcd_init(void)
{
    sw_press_init();
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();

}

lv_color_t set_color(t_color needed_color)
{
    lv_color_t color;

    switch (needed_color)
    {
    case RED:
        color = lv_color_make(255, 0, 0);
        break;
    case light_RED:
        color = lv_color_make(255, 99, 71);
        break;
    case dark_RED:
        color = lv_color_make(139, 0, 0);
        break;
    case GREEN:
        color = lv_color_make(0, 255, 0);
        break;
    case BLUE:
        color = lv_color_make(0, 0, 255);
        break;
    case YELLOW:
        color = lv_color_make(255, 255, 0);
        break;
    case BLACK:
        color = lv_color_make(0, 0, 0);
        break;
    case WHITE:
        color = lv_color_make(255, 255, 255);
        break;
    default:
        // Handle unrecognized color
        color = lv_color_make(255, 255, 255); // Default to white if color is not recognized
        break;
    }
    

    return color;
}
/*
lv_obj_t* text_init(TextParams params)
{
    lv_color_t txtcolor;
    
    if (params.with_background) {
        lv_color_t bgcolor;

        // Create a rectangle as the background
        lv_obj_t* bg = lv_obj_create(params.screen);
        lv_obj_set_size(bg, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_pos(bg, params.x, params.y);
        lv_color_t colorbg = set_color(params.bg_color);
        bgcolor = colorbg;
        lv_obj_set_style_bg_color(bg, bgcolor, LV_PART_MAIN);

        // Create a label for the text inside the background
        lv_obj_t* label = lv_label_create(bg);
        lv_label_set_text(label, params.text);
        lv_obj_align(label, LV_ALIGN_CENTER, 0, 0); // Align label to the center of the background


        lv_color_t color = set_color(params.txt_color);
        txtcolor = color;
        lv_obj_set_style_text_color(label, txtcolor, LV_PART_MAIN);

        if (params.font != NULL) {
            lv_obj_set_style_text_font(label, params.font, LV_PART_MAIN);
        }

        return bg;
    }
    else {
        lv_obj_t* label = lv_label_create(params.screen);
        lv_label_set_text(label, params.text);
        lv_obj_set_pos(label, params.x, params.y);
        lv_color_t color = set_color(params.txt_color);
        txtcolor = color;
        lv_obj_set_style_text_color(label, txtcolor, LV_PART_MAIN);

        if (params.font != NULL) {
        i need generic function i pass font ti it and object i mean object is label i create and apply text font on my this object
            lv_obj_set_style_text_font(label, params.font, LV_PART_MAIN);
        }
        return label;
    }
}

*/


void  screen_set_color(tbyte screenIndex, t_color screenColor)
{
   
    // Check if the screenIndex is within the valid range
    if (screenIndex < max_screens) {
        screenHolder.screens[screenIndex] = lv_obj_create(NULL);
        lv_obj_set_size(screenHolder.screens[screenIndex], LV_HOR_RES, LV_VER_RES); 
        lv_color_t color = set_color(screenColor);
        screenHolder.color[screenIndex] = color;
        lv_obj_set_style_bg_color(screenHolder.screens[screenIndex], screenHolder.color[screenIndex], LV_STATE_DEFAULT);  // Set background color
        lv_scr_load(screenHolder.screens[screenIndex]);  // Load the screen
    }
    else {
        // Handle the case where the screenIndex exceeds the maximum allowed value
    }
}


void Go_to_screen(tbyte screenIndex) {
    lv_scr_load(screenHolder.screens[screenIndex]);
}


lv_obj_t *button_init( ButtonParams params) 
{    

    lv_color_t bgcolor;
    lv_color_t labelcolor;
    lv_obj_t* button = lv_btn_create(params.screen);
    lv_obj_set_size(button, params.width, params.height);
    lv_obj_align(button, params.align, params.x_offset, params.y_offset);

    // Set the button background color
    lv_color_t colorbg = set_color(params.bg_color);
    bgcolor = colorbg;
    

    // Set the button background color using lv_obj_set_style_local_bg_color
    lv_obj_set_style_bg_color(button, bgcolor, LV_PART_MAIN );

    lv_obj_t* label = lv_label_create(button);
    lv_label_set_text(label, params.label_text);

    // Set the label text color
    lv_color_t color = set_color(params.label_color);
    labelcolor = color;
    // Set the label text color using lv_obj_set_style_local_text_color
    lv_obj_set_style_text_color(label, labelcolor, LV_STATE_DEFAULT );
    lv_obj_center(label);

    return button;
}







void label_create(tbyte screenIndex, tbyte textIndex)
{
    if (screenIndex < max_screens && textIndex < max_text)
    {
        lv_obj_t* label = lv_label_create(screenHolder.screens[screenIndex]);
        text_params[textIndex].screen = screenHolder.screens[screenIndex];
        lv_label_set_text(label, "");
    }
    else {
    }
}



void label_set_text(tbyte textIndex, const char* text) 
{
    if (textIndex < max_text) {
        text_params[textIndex].label = lv_label_create(text_params[textIndex].screen);
        lv_label_set_text(text_params[textIndex].label, text);
    }
    else {
    }
}


void label_set_color(tbyte textIndex, t_color txt_color)
{
    if (textIndex < max_text) {
        lv_color_t txtcolor = set_color(txt_color);
        lv_obj_set_style_text_color(text_params[textIndex].label, txtcolor, LV_PART_MAIN);
    }
    else {
    }
}

void label_set_position(tbyte textIndex, lv_coord_t x, lv_coord_t y) 
{
    if (textIndex < max_text) {
        lv_obj_t* label = text_params[textIndex].label;

        // Set the position for the label
        lv_obj_set_pos(label, x, y);
    }
    else {
    }
}


void label_set_font(tbyte textIndex, lv_font_t* font) 
{
    if (textIndex < max_text) {
        lv_obj_t* label = text_params[textIndex].label;
        lv_obj_set_style_text_font(label, font, LV_PART_MAIN);
    }
    else {
    }
}

void label_set_background(tbyte textIndex, const char* text, lv_coord_t x, lv_coord_t y, uint8_t bg_color, uint8_t txt_color, lv_font_t* font) {
    // Check if the textIndex is within the valid range
    if (textIndex < max_text) {
        // Create a rectangle as the background
        lv_obj_t* bg = lv_obj_create(text_params[textIndex].screen);
        lv_obj_set_size(bg, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_pos(bg, x, y);
        lv_color_t bcolor = set_color(bg_color);
        lv_obj_set_style_bg_color(bg, bcolor, LV_STATE_DEFAULT);

        // Create a label for the text inside the background
        lv_obj_t* label = lv_label_create(bg);
        lv_label_set_text(label, text);
        lv_obj_align(label, LV_ALIGN_CENTER, 0, 0); // Align label to the center of the background

        lv_color_t txtcolor = set_color(txt_color);
        lv_obj_set_style_text_color(label, txtcolor, LV_PART_MAIN);
        lv_obj_set_style_text_font(label, font, LV_STATE_DEFAULT);

        // Store the background reference in the TextParams structure
        text_params[textIndex].background = bg;
    }
    else {
        // Handle the case where the textIndex exceeds the maximum allowed value
    }
}



void label_remove(tbyte textIndex) 
{
    if (textIndex < max_text) {
        // Find the label corresponding to the specified textIndex
        lv_obj_t* label = text_params[textIndex].label;

        if (label != NULL) {
            // Delete the label if it exists
            lv_obj_del(label);
            text_params[textIndex].label = NULL;
        }

        // Find the background corresponding to the specified textIndex
        lv_obj_t* background = text_params[textIndex].background;

        if (background != NULL) {
            // Delete the background if it exists
            lv_obj_del(background);
            text_params[textIndex].background = NULL;
        }
    }
    else {
        // Handle the case where the textIndex exceeds the maximum allowed value
    }
}

