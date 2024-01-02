#ifndef MCAL_H
#define MCAL_H

#define ESP32S2 3


#define MCU ESP32S2
#if MCU == ESP32S2
#include "esp32s2/inc/mcal_esp32s2.h"
#elif MCU == ATMEGA32
#include "mcal_atmega32.h"
#elif MCU == HT66F489
#include "mcal_ht66f489.h"
#endif

#endif
