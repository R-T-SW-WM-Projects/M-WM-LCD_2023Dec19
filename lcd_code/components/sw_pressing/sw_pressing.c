#include "sw_pressing.h"
#include "std_types.h"
#include "model.h"
#include <esp_log.h>


#if SW_PULL_TYPE == SW_PULL_DOWN
    #define SW_LEVEL_PRESSED   HIGH
    #define SW_LEVEL_RELEASED  LOW
#elif SW_PULL_TYPE == SW_PULL_UP
    #define SW_LEVEL_PRESSED   LOW
    #define SW_LEVEL_RELEASED  HIGH
#endif

#define PRESSED 1
#define RELEASED 0


typedef struct{
    uint8_t state;
    gpio_num_t pin;
    uint8_t level;
    void (* notify)(void);
}sw_config_t;


sw_config_t sw[SW_MAX_NUM] = {
    {.state = RELEASED, .pin = GPIO_NUM_39, .level = SW_LEVEL_RELEASED, .notify = NULL},
    {.state = RELEASED, .pin = GPIO_NUM_40, .level = SW_LEVEL_RELEASED, .notify = wm_course_update},
    {.state = RELEASED, .pin = GPIO_NUM_41, .level = SW_LEVEL_RELEASED, .notify = wm_temp_update},
    {.state = RELEASED, .pin = GPIO_NUM_42, .level = SW_LEVEL_RELEASED, .notify = wm_dirtLevel_update}
};

void sw_press_init()
{
    for(int i = 0; i < SW_MAX_NUM; i++)
    {
        gpio_reset_pin(sw[i].pin);
        gpio_set_direction(sw[i].pin,  GPIO_MODE_OUTPUT);
        gpio_set_level(sw[i].pin, SW_LEVEL_RELEASED);
    }
}

void sw_press(sw_t i)
{
    sw[i].state = PRESSED;
}


void sw_press_update(void)
{
    for(int i = 0; i < SW_MAX_NUM; i++)
    {
        if(sw[i].state == PRESSED)
        {
            if (sw[i].level == SW_LEVEL_PRESSED)
            {
            //ESP_LOGI("SW_PRESS", "pressed sw %d", i);
                sw[i].level = SW_LEVEL_RELEASED;

                gpio_set_level(sw[i].pin, SW_LEVEL_RELEASED);

                sw[i].state = RELEASED;

                if(sw[i].notify != NULL)
                {
                    sw[i].notify();
                }
            }
            else
            {
                sw[i].level = SW_LEVEL_PRESSED;
                gpio_set_level(sw[i].pin, SW_LEVEL_PRESSED);
            }
        }
    }
}



