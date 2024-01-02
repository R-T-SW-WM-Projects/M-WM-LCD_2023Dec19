

#ifndef _SSD1963_CONST_
#define _SSD1963_CONST_

/*********************
 *    INCLUDE
 *********************/
#include "ssd1963_cfg.h"
#include "lvgl.h"

/*********************
 *      DEFINE
 *********************/

//LCD dimensions
#define SSD_HOR_RESOLUTION		(LV_HOR_RES_MAX)
#define SSD_VER_RESOLUTION		(LV_VER_RES_MAX)

/*********************
 *     TYPEDEF
 *********************/
/**
 * @brief Define all screen direction
 *
 */
typedef enum {
    /* @---> X
       |
       Y
    */
    SCR_DIR_LRTB,   /**< From left to right then from top to bottom, this consider as the original direction of the screen */

    /*  Y
        |
        @---> X
    */
    SCR_DIR_LRBT,   /**< From left to right then from bottom to top */

    /* X <---@
             |
             Y
    */
    SCR_DIR_RLTB,   /**< From right to left then from top to bottom */

    /*       Y
             |
       X <---@
    */
    SCR_DIR_RLBT,   /**< From right to left then from bottom to top */

    /* @---> Y
       |
       X
    */
    SCR_DIR_TBLR,   /**< From top to bottom then from left to right */

    /*  X
        |
        @---> Y
    */
    SCR_DIR_BTLR,   /**< From bottom to top then from left to right */

    /* Y <---@
             |
             X
    */
    SCR_DIR_TBRL,   /**< From top to bottom then from right to left */

    /*       X
             |
       Y <---@
    */
    SCR_DIR_BTRL,   /**< From bottom to top then from right to left */

    SCR_DIR_MAX,

    /* Another way to represent rotation with 3 bit*/
    SCR_MIRROR_X = 0x40, /**< Mirror X-axis */
    SCR_MIRROR_Y = 0x20, /**< Mirror Y-axis */
    SCR_SWAP_XY  = 0x80, /**< Swap XY axis */
} scr_dir_t;

typedef struct
{
// scr_interface_driver_t *interface_drv;
uint16_t original_width;
uint16_t original_height;
uint16_t width;
uint16_t height;
uint16_t offset_hor;
uint16_t offset_ver;
scr_dir_t dir;
} scr_handle_t;

typedef enum
{
    SSD_ORIENTATION_PORTRATE = SCR_DIR_TBRL,
    SSD_ORIENTATION_PORTRATE_INVERTED = SCR_DIR_BTLR,
    SSD_ORIENTATION_LANDSCAPE = SCR_DIR_LRTB,
    SSD_ORIENTATION_LANDSCAPE_INVERTED = SCR_DIR_RLBT
} ssd_orientation_t;


/********************
 *      CONSTS
 ********************/
//Calculated values
#define SSD_HT	(SSD_HOR_RESOLUTION+SSD_HOR_BACK_PORCH+SSD_HOR_FRONT_PORCH)
#define SSD_HPS	(SSD_HOR_BACK_PORCH)
#define SSD_VT 	(SSD_VER_RESOLUTION+SSD_VER_BACK_PORCH+SSD_VER_FRONT_PORCH)
#define SSD_VPS (SSD_VER_BACK_PORCH)


// COMMANDS CONSTANTS
#define SSD1963_CASET   0x2A
#define SSD1963_RASET   0x2B
#define SSD1963_RAMWR   0x2C
#define SSD1963_MADCTL  0x36


/* MADCTL Defines */
//BITS OF ROTATION COMMAND
#define MADCTL_MY  0x01
#define MADCTL_MX  0x02
#define MADCTL_MV  0x20
#define MADCTL_ML  0x10
#define MADCTL_RGB 0x08
#define MADCTL_MH  0x04


#endif
