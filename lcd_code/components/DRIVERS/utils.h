/**
 * Author: ASHRAF
 * 
 */

#ifndef UTILS_H
#define	UTILS_H

#ifdef	__cplusplus
extern "C" {
#endif
/*********************
 *      INCLUDES
 *********************/
/*********************
 *      DEFINES
 *********************/
#define BIT_CONFIG(reg ,bit_postion ,value)     reg = ((reg) & ~(1<<bit_postion)) | ((value & 0x01) << bit_postion)
#define BIT_SET(reg, bit_mask)                    reg |= bit_mask
#define BIT_CLR(reg, bit_mask)                    reg &= ~bit_mask
#define BIT_GET(reg, bit_mask)                    (reg & bit_mask)
#define BIT_TOGGLE(reg, bit_mask)                 reg ^= bit_mask
#define BIT_SET_POSITION(reg, val, pos)         reg |= val << pos
#define IS_ODD(num)                             (num & 0x01)


#define FREQ_HZ_TO_PERIOD_US(freq_hz)          (uint32_t)((1/(float)(freq_hz))*1000000)
/**********************
 *      TYPEDEFS
 **********************/


/**********************
 * GLOBAL VARIABLES
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
/**********************
 *  STATIC VARIABLES
 **********************/
#ifdef	__cplusplus
}
#endif

#endif

