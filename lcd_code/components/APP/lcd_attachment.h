#ifndef  LCD_ATTACHMENT_H_
#define  LCD_ATTACHMENT_H_

lv_obj_t* textLabels[max_screens][max_text];

typedef struct {
    lv_color_t color[max_screens];
    lv_obj_t* screens[max_screens];

} screenparam;


screenparam screenHolder;

typedef struct {
    lv_obj_t* screen;
    const char* text;
    lv_obj_t* label;  // Store the label here
    lv_coord_t x;
    lv_coord_t y;
    uint8_t bg_color;
    bool with_background;
    uint8_t txt_color;
    lv_font_t* font;
    lv_obj_t* background; // New field to store the background reference
} TextParams;



#endif

