/* LVGL Example project
 * Basic project to test LVGL on ESP32 based projects.
 * This example code is in the Public Domain (or CC0 licensed, at your option.)
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
 */
#include <stdio.h>
#include "esp_log.h"
#include "lvgl.h"
#include "OS/tt_scheduler.h"
#include "comm_uart/comm_uart.h"
#include "ssd1963/ssd1963.h"
#include "../components/APP/lcd.h"
#include "../components\lvgl\src\font\arial_40.c"


void app_main()
{

    tt_init();
    lcd_init();

    screen_set_color(0, RED);
    screen_set_color(1, YELLOW);
    screen_set_color(2, GREEN);

    Go_to_screen(0);
    
    label_create(0, 1);
    label_create(0, 2);



    //label_set_text_params(0, "ahmed", 0, 0, BLUE, WHITE, &lv_font_montserrat_48, false);
    //label_set_text_params(1, "embedded", 30, 150, GREEN, YELLOW, &lv_font_montserrat_48, true);
    label_set_text(1, "ahmed");
    label_set_position(1, 50, 50);
    label_set_color(1, BLUE);
    label_set_font(1,&lv_font_montserrat_48);
    label_set_background(2, "ahlawy",100,100,BLUE,BLACK, &lv_font_montserrat_20);

   



    /*
     ButtonParams button = {
         .screen = screenHolder.screens[2],
        .label_text = "EL_Araby صناع الثقة ",
        .align = LV_ALIGN_CENTER,
        .x_offset = 0,
        .y_offset = 0,
        .width = 170,
        .height = 80,
        .bg_color = BLUE,
        .label_color = YELLOW
    };
     
     ButtonParams button55 = {
         .screen = screenHolder.screens[2],
        .label_text = "Press me",
        .align = LV_ALIGN_TOP_RIGHT,
        .x_offset = 0,
        .y_offset = 0,
        .width = 100,
        .height = 50,
        .bg_color = GREEN,
        .label_color = BLUE
     };
      button_init(button);
     button_init(button55);


  

    TextParams params2 = {
        .screen= screenHolder.screens[2],
        .text = "Ahmed Yasser Mostafa",
        .x = 60,
        .y = 300,
        .bg_color = BLUE,
        .txt_color = BLACK,
        .font = &arial_40,
        .with_background = false
    };
    
    TextParams params9 = {
        .screen = screenHolder.screens[0],
        .text = "Embedded sw enginner",
        .x = 0,
        .y = 0,
        .bg_color = GREEN,
        .txt_color = BLACK,
        .font = &lv_font_montserrat_18,
        .with_background = true
    };

    TextParams params5 = {
       .screen = screenHolder.screens[1],
       .text = "احمد ياسر مصطفى محمد",
       .x = 90,
       .y = 60,
       .bg_color = BLUE,
       .txt_color = RED,
       .font = &lv_font_dejavu_16_persian_hebrew,
       .with_background = false
    };
    
        TextParams params4 = {
       .screen = screenHolder.screens[2],
       .text = LV_SYMBOL_AUDIO,
       .x = 0,
       .y = 60,
       .bg_color = GREEN,
       .txt_color = BLACK,
       .font = &lv_font_dejavu_16_persian_hebrew,
       .with_background = true
    };

    text_init(params2);
    text_init(params4);
    text_init(params5);
    text_init(params9);
    
    */


     void lv_tick_task(void) {
        //ESP_LOGI("tick","");
        lv_tick_inc(2);
    }
    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &lv_tick_task,
        .name = "periodic_gui"
    };
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, 2 * 1000));
    tt_add_task(call_idle_task, ((CONFIG_TASK_WDT_TIMEOUT_S / 2) * 1000) / TT_TICK_MS, (CONFIG_TASK_WDT_TIMEOUT_S * 1000) / TT_TICK_MS);
    tt_add_task(lv_task_handler,10, 10);
    tt_add_task(sw_press_update, 200, 500);
    tt_start();
    while (1)
    {
        tt_dispatch_task();
    }
}

