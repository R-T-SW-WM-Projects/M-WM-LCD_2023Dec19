// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.0
// LVGL version: 8.3.4
// Project name: wm_ui

#include "../ui.h"

void ui_Screen2_screen_init(void)
{
    ui_Screen2 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Panel_s2 = lv_obj_create(ui_Screen2);
    lv_obj_set_width(ui_Panel_s2, 447);
    lv_obj_set_height(ui_Panel_s2, 187);
    lv_obj_set_x(ui_Panel_s2, -1);
    lv_obj_set_y(ui_Panel_s2, 29);
    lv_obj_set_align(ui_Panel_s2, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel_s2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Panel_s2, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel_s2, lv_color_hex(0x283C47), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel_s2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ImageIconS2 = lv_img_create(ui_Screen2);
    lv_img_set_src(ui_ImageIconS2, &ui_img_1342514607);
    lv_obj_set_width(ui_ImageIconS2, LV_SIZE_CONTENT);   /// 51
    lv_obj_set_height(ui_ImageIconS2, LV_SIZE_CONTENT);    /// 51
    lv_obj_set_x(ui_ImageIconS2, 190);
    lv_obj_set_y(ui_ImageIconS2, -100);
    lv_obj_set_align(ui_ImageIconS2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ImageIconS2, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_ImageIconS2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label_timer_s2 = lv_label_create(ui_Screen2);
    lv_obj_set_width(ui_Label_timer_s2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label_timer_s2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label_timer_s2, -165);
    lv_obj_set_y(ui_Label_timer_s2, -100);
    lv_obj_set_align(ui_Label_timer_s2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label_timer_s2, "00:00");
    lv_obj_set_style_text_color(ui_Label_timer_s2, lv_color_hex(0xD0CFCD), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label_timer_s2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label_timer_s2, &ui_font_DSDIGI_50, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Button3 = lv_btn_create(ui_Screen2);
    lv_obj_set_width(ui_Button3, 110);
    lv_obj_set_height(ui_Button3, 50);
    lv_obj_set_x(ui_Button3, 105);
    lv_obj_set_y(ui_Button3, 125);
    lv_obj_set_align(ui_Button3, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Button3, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Button3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Button3, lv_color_hex(0xB3CDE0), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Button3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Button3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Button3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_Button3, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_Button3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui_Button3, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui_Button3, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label8 = lv_label_create(ui_Button3);
    lv_obj_set_width(ui_Label8, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label8, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label8, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label8, "Options");
    lv_obj_set_style_text_color(ui_Label8, lv_color_hex(0x2271A4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label8, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label8, &ui_font_montregular22, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Button6 = lv_btn_create(ui_Screen2);
    lv_obj_set_width(ui_Button6, 110);
    lv_obj_set_height(ui_Button6, 50);
    lv_obj_set_x(ui_Button6, -118);
    lv_obj_set_y(ui_Button6, 125);
    lv_obj_set_align(ui_Button6, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Button6, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Button6, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Button6, lv_color_hex(0x005B96), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Button6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Button6, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Button6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_Button6, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_Button6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui_Button6, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui_Button6, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Button6, &ui_font_montregular22, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label10 = lv_label_create(ui_Button6);
    lv_obj_set_width(ui_Label10, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label10, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label10, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label10, "Program");
    lv_obj_set_style_text_color(ui_Label10, lv_color_hex(0xE8F0F5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label10, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Button5 = lv_btn_create(ui_Screen2);
    lv_obj_set_width(ui_Button5, 130);
    lv_obj_set_height(ui_Button5, 50);
    lv_obj_set_x(ui_Button5, -4);
    lv_obj_set_y(ui_Button5, 123);
    lv_obj_set_align(ui_Button5, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Button5, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Button5, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Button5, lv_color_hex(0x6497B1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Button5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Button5, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Button5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_Button5, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_Button5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui_Button5, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui_Button5, 1, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label9 = lv_label_create(ui_Button5);
    lv_obj_set_width(ui_Label9, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label9, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label9, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label9, "Edit");
    lv_obj_set_style_text_color(ui_Label9, lv_color_hex(0xC6CACA), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label9, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label9, &ui_font_montregular22, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PanelRins = lv_obj_create(ui_Screen2);
    lv_obj_set_width(ui_PanelRins, 135);
    lv_obj_set_height(ui_PanelRins, 45);
    lv_obj_set_x(ui_PanelRins, -146);
    lv_obj_set_y(ui_PanelRins, -19);
    lv_obj_set_align(ui_PanelRins, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_PanelRins, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_PanelRins, lv_color_hex(0xE4E4E4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelRins, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelRinsS2 = lv_label_create(ui_PanelRins);
    lv_obj_set_width(ui_LabelRinsS2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelRinsS2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelRinsS2, 1);
    lv_obj_set_y(ui_LabelRinsS2, 13);
    lv_obj_set_align(ui_LabelRinsS2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelRinsS2, "RINS");
    lv_obj_set_style_text_color(ui_LabelRinsS2, lv_color_hex(0x6497B1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelRinsS2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelRinsS2, &ui_font_mont_bold_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_RollerRinsS2 = lv_roller_create(ui_PanelRins);
    lv_roller_set_options(ui_RollerRinsS2, g_str_rins, LV_ROLLER_MODE_NORMAL);
    lv_obj_set_height(ui_RollerRinsS2, 28);
    lv_obj_set_width(ui_RollerRinsS2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_RollerRinsS2, -2);
    lv_obj_set_y(ui_RollerRinsS2, -6);
    lv_obj_set_align(ui_RollerRinsS2, LV_ALIGN_CENTER);
    lv_obj_set_style_text_color(ui_RollerRinsS2, lv_color_hex(0x4F8AB1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_RollerRinsS2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_RollerRinsS2, &ui_font_montregular16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_RollerRinsS2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_RollerRinsS2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_RollerRinsS2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_RollerRinsS2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_color(ui_RollerRinsS2, lv_color_hex(0x4F8AB1), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_RollerRinsS2, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_RollerRinsS2, lv_color_hex(0xFFFFFF), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_RollerRinsS2, 0, LV_PART_SELECTED | LV_STATE_DEFAULT);

    ui_PanelWaterTemp6 = lv_obj_create(ui_Screen2);
    lv_obj_set_width(ui_PanelWaterTemp6, 135);
    lv_obj_set_height(ui_PanelWaterTemp6, 45);
    lv_obj_set_x(ui_PanelWaterTemp6, -146);
    lv_obj_set_y(ui_PanelWaterTemp6, 53);
    lv_obj_set_align(ui_PanelWaterTemp6, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_PanelWaterTemp6, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_PanelWaterTemp6, lv_color_hex(0xE4E4E4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelWaterTemp6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelTimeS2 = lv_label_create(ui_PanelWaterTemp6);
    lv_obj_set_width(ui_LabelTimeS2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelTimeS2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelTimeS2, 1);
    lv_obj_set_y(ui_LabelTimeS2, 13);
    lv_obj_set_align(ui_LabelTimeS2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelTimeS2, "WASH TIME");
    lv_obj_set_style_text_color(ui_LabelTimeS2, lv_color_hex(0x6497B1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelTimeS2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelTimeS2, &ui_font_mont_bold_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_RollerTimeS2 = lv_roller_create(ui_PanelWaterTemp6);
    lv_roller_set_options(ui_RollerTimeS2, g_str_washTime, LV_ROLLER_MODE_NORMAL);
    lv_obj_set_height(ui_RollerTimeS2, 28);
    lv_obj_set_width(ui_RollerTimeS2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_RollerTimeS2, -2);
    lv_obj_set_y(ui_RollerTimeS2, -6);
    lv_obj_set_align(ui_RollerTimeS2, LV_ALIGN_CENTER);
    lv_obj_set_style_text_color(ui_RollerTimeS2, lv_color_hex(0x4F8AB1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_RollerTimeS2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_RollerTimeS2, &ui_font_montregular16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_RollerTimeS2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_RollerTimeS2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_RollerTimeS2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_RollerTimeS2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_color(ui_RollerTimeS2, lv_color_hex(0x4F8AB1), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_RollerTimeS2, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_RollerTimeS2, lv_color_hex(0xFFFFFF), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_RollerTimeS2, 0, LV_PART_SELECTED | LV_STATE_DEFAULT);

    ui_PanelWaterTemp7 = lv_obj_create(ui_Screen2);
    lv_obj_set_width(ui_PanelWaterTemp7, 135);
    lv_obj_set_height(ui_PanelWaterTemp7, 45);
    lv_obj_set_x(ui_PanelWaterTemp7, 2);
    lv_obj_set_y(ui_PanelWaterTemp7, 54);
    lv_obj_set_align(ui_PanelWaterTemp7, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_PanelWaterTemp7, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_PanelWaterTemp7, lv_color_hex(0xE4E4E4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelWaterTemp7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelSuperSpinS2 = lv_label_create(ui_PanelWaterTemp7);
    lv_obj_set_width(ui_LabelSuperSpinS2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelSuperSpinS2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelSuperSpinS2, 1);
    lv_obj_set_y(ui_LabelSuperSpinS2, 13);
    lv_obj_set_align(ui_LabelSuperSpinS2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelSuperSpinS2, "SUPER SPIN");
    lv_obj_set_style_text_color(ui_LabelSuperSpinS2, lv_color_hex(0x6497B1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelSuperSpinS2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelSuperSpinS2, &ui_font_mont_bold_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_RollerSuperSpinS2 = lv_roller_create(ui_PanelWaterTemp7);
    lv_roller_set_options(ui_RollerSuperSpinS2, g_str_superSpin, LV_ROLLER_MODE_NORMAL);
    lv_obj_set_height(ui_RollerSuperSpinS2, 28);
    lv_obj_set_width(ui_RollerSuperSpinS2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_RollerSuperSpinS2, -2);
    lv_obj_set_y(ui_RollerSuperSpinS2, -6);
    lv_obj_set_align(ui_RollerSuperSpinS2, LV_ALIGN_CENTER);
    lv_obj_set_style_text_color(ui_RollerSuperSpinS2, lv_color_hex(0x4F8AB1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_RollerSuperSpinS2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_RollerSuperSpinS2, &ui_font_montregular16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_RollerSuperSpinS2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_RollerSuperSpinS2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_RollerSuperSpinS2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_RollerSuperSpinS2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_color(ui_RollerSuperSpinS2, lv_color_hex(0x4F8AB1), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_RollerSuperSpinS2, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_RollerSuperSpinS2, lv_color_hex(0xFFFFFF), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_RollerSuperSpinS2, 0, LV_PART_SELECTED | LV_STATE_DEFAULT);

    ui_PanelWaterTemp8 = lv_obj_create(ui_Screen2);
    lv_obj_set_width(ui_PanelWaterTemp8, 135);
    lv_obj_set_height(ui_PanelWaterTemp8, 45);
    lv_obj_set_x(ui_PanelWaterTemp8, 2);
    lv_obj_set_y(ui_PanelWaterTemp8, -18);
    lv_obj_set_align(ui_PanelWaterTemp8, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_PanelWaterTemp8, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_PanelWaterTemp8, lv_color_hex(0xE4E4E4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelWaterTemp8, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelTempS2 = lv_label_create(ui_PanelWaterTemp8);
    lv_obj_set_width(ui_LabelTempS2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelTempS2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelTempS2, 1);
    lv_obj_set_y(ui_LabelTempS2, 13);
    lv_obj_set_align(ui_LabelTempS2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelTempS2, "WATER TEMP,");
    lv_obj_set_style_text_color(ui_LabelTempS2, lv_color_hex(0x6497B1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelTempS2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelTempS2, &ui_font_mont_bold_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_RollerTempS2 = lv_roller_create(ui_PanelWaterTemp8);
    lv_roller_set_options(ui_RollerTempS2, g_str_waterTemp, LV_ROLLER_MODE_NORMAL);
    lv_obj_set_height(ui_RollerTempS2, 28);
    lv_obj_set_width(ui_RollerTempS2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_RollerTempS2, -2);
    lv_obj_set_y(ui_RollerTempS2, -6);
    lv_obj_set_align(ui_RollerTempS2, LV_ALIGN_CENTER);
    lv_obj_set_style_text_color(ui_RollerTempS2, lv_color_hex(0x4F8AB1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_RollerTempS2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_RollerTempS2, &ui_font_montregular16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_RollerTempS2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_RollerTempS2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_RollerTempS2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_RollerTempS2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_color(ui_RollerTempS2, lv_color_hex(0x4F8AB1), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_RollerTempS2, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_RollerTempS2, lv_color_hex(0xFFFFFF), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_RollerTempS2, 0, LV_PART_SELECTED | LV_STATE_DEFAULT);

    ui_PanelLevelS2 = lv_obj_create(ui_Screen2);
    lv_obj_set_width(ui_PanelLevelS2, 135);
    lv_obj_set_height(ui_PanelLevelS2, 45);
    lv_obj_set_x(ui_PanelLevelS2, 145);
    lv_obj_set_y(ui_PanelLevelS2, -19);
    lv_obj_set_align(ui_PanelLevelS2, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_PanelLevelS2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_PanelLevelS2, lv_color_hex(0xE4E4E4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelLevelS2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelLevelS2 = lv_label_create(ui_PanelLevelS2);
    lv_obj_set_width(ui_LabelLevelS2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelLevelS2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelLevelS2, 1);
    lv_obj_set_y(ui_LabelLevelS2, 13);
    lv_obj_set_align(ui_LabelLevelS2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelLevelS2, "WATER LEVEL");
    lv_obj_set_style_text_color(ui_LabelLevelS2, lv_color_hex(0x6497B1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelLevelS2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelLevelS2, &ui_font_mont_bold_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_RollerLevelS2 = lv_roller_create(ui_PanelLevelS2);
    lv_roller_set_options(ui_RollerLevelS2, g_str_waterLevel, LV_ROLLER_MODE_NORMAL);
    lv_obj_set_height(ui_RollerLevelS2, 28);
    lv_obj_set_width(ui_RollerLevelS2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_RollerLevelS2, -2);
    lv_obj_set_y(ui_RollerLevelS2, -6);
    lv_obj_set_align(ui_RollerLevelS2, LV_ALIGN_CENTER);
    lv_obj_set_style_text_color(ui_RollerLevelS2, lv_color_hex(0x4F8AB1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_RollerLevelS2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_RollerLevelS2, &ui_font_montregular16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_RollerLevelS2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_RollerLevelS2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_RollerLevelS2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_RollerLevelS2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_color(ui_RollerLevelS2, lv_color_hex(0x4F8AB1), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_RollerLevelS2, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_RollerLevelS2, lv_color_hex(0xFFFFFF), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_RollerLevelS2, 0, LV_PART_SELECTED | LV_STATE_DEFAULT);

    ui_PanelSpin = lv_obj_create(ui_Screen2);
    lv_obj_set_width(ui_PanelSpin, 135);
    lv_obj_set_height(ui_PanelSpin, 45);
    lv_obj_set_x(ui_PanelSpin, 143);
    lv_obj_set_y(ui_PanelSpin, 54);
    lv_obj_set_align(ui_PanelSpin, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_PanelSpin, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_PanelSpin, lv_color_hex(0xE4E4E4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PanelSpin, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelSpinS2 = lv_label_create(ui_PanelSpin);
    lv_obj_set_width(ui_LabelSpinS2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelSpinS2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelSpinS2, 1);
    lv_obj_set_y(ui_LabelSpinS2, 13);
    lv_obj_set_align(ui_LabelSpinS2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelSpinS2, "SPIN");
    lv_obj_set_style_text_color(ui_LabelSpinS2, lv_color_hex(0x6497B1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelSpinS2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelSpinS2, &ui_font_mont_bold_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_RollerSpinS2 = lv_roller_create(ui_PanelSpin);
    lv_roller_set_options(ui_RollerSpinS2, g_str_spin, LV_ROLLER_MODE_NORMAL);
    lv_obj_set_height(ui_RollerSpinS2, 28);
    lv_obj_set_width(ui_RollerSpinS2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_RollerSpinS2, -2);
    lv_obj_set_y(ui_RollerSpinS2, -6);
    lv_obj_set_align(ui_RollerSpinS2, LV_ALIGN_CENTER);
    lv_obj_set_style_text_color(ui_RollerSpinS2, lv_color_hex(0x4F8AB1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_RollerSpinS2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_RollerSpinS2, &ui_font_montregular16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_RollerSpinS2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_RollerSpinS2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_RollerSpinS2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_RollerSpinS2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_color(ui_RollerSpinS2, lv_color_hex(0x4F8AB1), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_RollerSpinS2, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_RollerSpinS2, lv_color_hex(0xFFFFFF), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_RollerSpinS2, 0, LV_PART_SELECTED | LV_STATE_DEFAULT);

    ui_Button10 = lv_btn_create(ui_Screen2);
    lv_obj_set_width(ui_Button10, 110);
    lv_obj_set_height(ui_Button10, 42);
    lv_obj_set_x(ui_Button10, -28);
    lv_obj_set_y(ui_Button10, -100);
    lv_obj_set_align(ui_Button10, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Button10, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Button10, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Button10, lv_color_hex(0x005B96), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Button10, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Button10, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Button10, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_Button10, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_Button10, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui_Button10, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui_Button10, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Button10, &ui_font_montregular22, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label2 = lv_label_create(ui_Button10);
    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label2, "Program");
    lv_obj_set_style_text_color(ui_Label2, lv_color_hex(0xE8F0F5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_Button3, ui_event_Button3, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Button6, ui_event_Button6, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Button10, ui_event_Button10, LV_EVENT_ALL, NULL);

}