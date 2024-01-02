#include <driver/gpio.h>

typedef enum{
    SW_START = 0,
    SW_COURSE,
    SW_TEMP ,
    SW_DIRT ,
    SW_MAX_NUM
}sw_t;

#define SW_PULL_DOWN  0
#define SW_PULL_UP    1
#define SW_PULL_TYPE SW_PULL_DOWN

void sw_press_init();
void sw_press(sw_t sw);
void sw_press_update(void);