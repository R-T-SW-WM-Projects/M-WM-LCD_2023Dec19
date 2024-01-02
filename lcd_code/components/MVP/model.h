#ifndef _MODEL_H_
#define _MODEL_H_

typedef enum {
  WM_COURSE_REGULAR = 0,
  WM_COURSE_HEAVY,
  WM_COURSE_QUICK,
  WM_COURSE_BLANKET,
  WM_COURSE_DELICATE,
  WM_COURSE_MEMORY,
  WM_COURSE_MAX
} wm_course_t;

typedef enum
{
    WM_TEMP_HOT,
    WM_TEMP_WARM,
    WM_TEMP_COLD,
    WM_TEMP_MAX
} wm_temp_t;

typedef enum
{
    WM_DIRT_LEVEL0 = 0,
    WM_DIRT_LEVEL1,
    WM_DIRT_LEVEL2,
    WM_DIRT_LEVEL3,
    WM_DIRT_MAX
} wm_dirt_t;

wm_course_t wm_get_course(void);
wm_temp_t wm_get_temp(void);
void wm_start(void);
void wm_pause(void);

void wm_set_course(wm_course_t course);
void wm_set_temp(wm_temp_t temp);
void wm_set_dirtLevel(wm_dirt_t level);

void wm_course_update(void);
void wm_temp_update(void);
void wm_dirtLevel_update(void);


#endif