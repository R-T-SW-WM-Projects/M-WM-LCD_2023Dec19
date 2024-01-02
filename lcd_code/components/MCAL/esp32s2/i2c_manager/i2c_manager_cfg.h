#ifndef _I2C_MANAGER_CFG_H_
#define _I2C_MANAGER_CFG_H_

#include "mcal.h"

#define I2C_MANAGER_0_ENABLED 1
		
	#if I2C_MANAGER_0_ENABLED == 1
		#define I2C_MANAGER_0_SDA PIN_4

		#define I2C_MANAGER_0_SCL PIN_5

		#define I2C_MANAGER_0_FREQ_HZ 400000
				/*The clock speed in Hz. Ranges from 100000 (100 kHz) to
				5000000 (5 Mhz). I2C buses that involve external wires may
				have to be slower, and the real maximum speed the bus will
				support depends on the value of the pullup resistors and the
				design of the overall circuit.
                
                range 100000 5000000
                 */

		#define I2C_MANAGER_0_TIMEOUT 20
				/*Timeout for I2C read and write operations. This does not
				include the time waiting for a lock.
                
                range 10 1000
                */
               
		#define I2C_MANAGER_0_LOCK_TIMEOUT 50
				/*Timeout at which point an operation waiting for its turn on
				the port will assume that whatever set the lock has died and
				overrides it. Set this somewhat larger than the previous
				timeout.
                
                range 10 1000
                */

		#define I2C_MANAGER_0_PULLUPS  false
    #endif



#define I2C_MANAGER_1_ENABLED 0
		
	#if I2C_MANAGER_1_ENABLED == 1
		#define I2C_MANAGER_1_SDA GPIO_PIN8

		#define I2C_MANAGER_1_SCL GPIO_PIN9

		#define I2C_MANAGER_1_FREQ_HZ 400000

		#define I2C_MANAGER_1_TIMEOUT 20

		#define I2C_MANAGER_1_LOCK_TIMEOUT 50

		#define I2C_MANAGER_1_PULLUPS
    #endif
       

#endif/*end of file*/