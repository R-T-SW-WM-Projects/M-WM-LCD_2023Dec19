#include "model.h"
#include "sw_pressing.h"

static wm_course_t g_current_course = WM_COURSE_REGULAR, g_required_course = WM_COURSE_REGULAR;
static wm_temp_t g_current_temp = WM_TEMP_WARM;
static wm_temp_t g_required_temp = WM_TEMP_WARM;


static wm_temp_t g_current_dirt = WM_DIRT_LEVEL1;
static wm_temp_t g_required_dirt = WM_DIRT_LEVEL1;

wm_course_t wm_get_course(void)
{
    return g_current_course;
}
wm_temp_t wm_get_temp(void)
{
    return g_current_temp;
}
void wm_start(void)
{
    sw_press(SW_START);
}
void wm_pause(void)
{
    wm_start();
}

void wm_set_course(wm_course_t course)
{
    g_required_course = course;
    wm_course_update();
}

void wm_set_temp(wm_temp_t temp)
{
    g_required_temp = temp;
    wm_temp_update();
}

void wm_set_dirtLevel(wm_dirt_t level)
{
    g_required_dirt = level;
    wm_dirtLevel_update();
}

static void iterator_increment(int * iterator, int max_value)
{
    (*iterator)++;
    if(*iterator >= max_value)
    {
        *iterator = 0;
    }
}

static void iterator_decrement(int * iterator, int max_value)
{
    (*iterator)--;
    if(*iterator <= -1)
    {
        *iterator = max_value-1;
    }
}

void wm_course_update(void)
{
    if(g_current_course == g_required_course)
    {
        return;
    }
    else
    {
        sw_press(SW_COURSE);

        iterator_increment(&g_current_course, WM_COURSE_MAX);
    }
}
void wm_temp_update(void)
{
    if(g_current_temp == g_required_temp)
    {
        return;
    }
    else
    {
        sw_press(SW_TEMP);

        iterator_increment(&g_current_temp, WM_TEMP_MAX);
    }
}


void wm_dirtLevel_update(void)
{
    if(g_current_dirt == g_required_dirt)
    {
        return;
    }
    else
    {
        sw_press(SW_DIRT);

        iterator_increment(&g_current_dirt, WM_DIRT_MAX);
    }
}