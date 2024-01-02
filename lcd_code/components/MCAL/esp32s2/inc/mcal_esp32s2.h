#ifndef _MCAL_H_
#define _MCAL_H_

//#include "TMPM370.h"
//#include "tx03_common.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../../mcal.h"
#include "driver/gpio.h"
#include "uart.h"
#include "i2c_manager.h"
/******************************************************************************/
// gpio

#define GPIO_NC  -1
#define GPIO_PIN_NC -1

#define PIN_0   GPIO_NUM_0 
#define PIN_1   GPIO_NUM_1 
#define PIN_2   GPIO_NUM_2 
#define PIN_3   GPIO_NUM_3 
#define PIN_4   GPIO_NUM_4 
#define PIN_5   GPIO_NUM_5 
#define PIN_6   GPIO_NUM_6 
#define PIN_7   GPIO_NUM_7 
#define PIN_8   GPIO_NUM_8 
#define PIN_9   GPIO_NUM_9 
#define PIN_10  GPIO_NUM_10
#define PIN_11  GPIO_NUM_11
#define PIN_12  GPIO_NUM_12
#define PIN_13  GPIO_NUM_13
#define PIN_14  GPIO_NUM_14
#define PIN_15  GPIO_NUM_15
#define PIN_16  GPIO_NUM_16
#define PIN_17  GPIO_NUM_17
#define PIN_18  GPIO_NUM_18
#define PIN_19  GPIO_NUM_19
#define PIN_20  GPIO_NUM_20
#define PIN_21  GPIO_NUM_21
#if CONFIG_IDF_TARGET_ESP32
#define PIN_22  GPIO_NUM_22
#define PIN_23  GPIO_NUM_23
#define PIN_24  GPIO_NUM_24
#define PIN_25  GPIO_NUM_25
#endif
#define PIN_26  GPIO_NUM_26
#define PIN_27  GPIO_NUM_27
#define PIN_28  GPIO_NUM_28
#define PIN_29  GPIO_NUM_29
#define PIN_30  GPIO_NUM_30 
#define PIN_31  GPIO_NUM_31
#define PIN_32  GPIO_NUM_32
#define PIN_33  GPIO_NUM_33 
#define PIN_34  GPIO_NUM_34 
#define PIN_35  GPIO_NUM_35 
#define PIN_36  GPIO_NUM_36 
#define PIN_37  GPIO_NUM_37 
#define PIN_38  GPIO_NUM_38 
#define PIN_39  GPIO_NUM_39 
#if GPIO_PIN_COUNT > 40
#define PIN_40  GPIO_NUM_40 
#define PIN_41  GPIO_NUM_41 
#define PIN_42  GPIO_NUM_42 
#define PIN_43  GPIO_NUM_43 
#define PIN_44  GPIO_NUM_44 
#define PIN_45  GPIO_NUM_45 
#define PIN_46  GPIO_NUM_46 
#endif

#define MCAL_GPIO_PIN_ALL GPIO_NUM_ALL




void mcal_gpio_init(void);
 
#define mcal_gpio_set_level(port, pin, level)      gpio_set_level(pin, level)
#define mcal_gpio_set_direction(port, pin, dir)    gpio_set_direction(pin, level)

/********************************************************************************/
// clock generator


/********************************************************************************/
// comm8080


void mcal_comm8080_init();
void mcal_comm8080_write_data(uint16_t data);
void mcal_comm8080_write_cmd(uint16_t cmd);
void mcal_comm8080_write(const uint8_t *data, uint32_t length);
esp_err_t mcal_comm8080_acquire(void);
esp_err_t mcal_comm8080_release(void);



/********************************************************************************/
// systick


/********************************************************************************/
// uart

/********************************************************************************/
// timer


/********************************************************************************/
// pwm


/********************************************************************************/
// adc


#endif
