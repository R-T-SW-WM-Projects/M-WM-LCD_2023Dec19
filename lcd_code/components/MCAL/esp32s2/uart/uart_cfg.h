#ifndef _UART_CFG_H_
#define _UART_CFG_H_

#include "mcal.h"


/**
 * enable locking mechanism for shared resources protection
 * @note be enabled with FREERTOS only
 */
#define UART_LOCKING_ENABLED    0

#define UART_0_ENABLED 1
		
	#if UART_0_ENABLED == 1
		#define UART_0_TX PIN_43

		#define UART_0_RX PIN_44

        #define UART_0_FLOWCTR_ENABLED 0

        #if UART_0_FLOWCTR_ENABALED
            #define UART_0_RTS  GPIO_PIN_5
            #define UART_0_CTS  GPIO_PIN_6
        #endif

		#define UART_0_BAUDRATE    115200

        #define UART_0_PARITY      UART_PARITY_DISABLE
        #define UART_0_STOP_BITS   1

        #define UART_0_WORD_LENGTH   UART_DATA_8_BITS /*!< Specifies the UART Word length.
                                                         This parameter can be a value of @ref uart_word_length_t */
                                                         
        #if UART_LOCKING_ENABLED	
		#define UART_0_LOCK_TIMEOUT 50
				/*Timeout at which point an operation waiting for its turn on
				the port will assume that whatever set the lock has died and
				overrides it. Set this somewhat larger than the previous
				timeout.
                
                range 10 1000
                */
        #endif
    #endif



#define UART_1_ENABLED 0
		
	#if UART_1_ENABLED == 1

		#define UART_1_TX GPIO_PIN9
		#define UART_1_RX GPIO_PIN8

        #define UART_1_FLOWCTR_ENABLED 0

        #if UART_1_FLOWCTR_ENABALED == 1
            #define UART_1_RTS  GPIO_PIN_5
            #define UART_1_CTS  GPIO_PIN_6
        #endif

		#define UART_1_BAUDRATE    115200
        #define UART_1_PARITY      UART_PARITY_DISABLE
        #define UART_1_STOP_BITS   1

        #define UART_1_WORD_LENGTH   UART_DATA_8_BITS /*!< Specifies the UART Word length.
                                                         This parameter can be a value of @ref uart_word_length_t */
                                                        
        #if UART_LOCKING_ENABLED == 1	
		    #define UART_1_LOCK_TIMEOUT 50
        #endif

    #endif
       

#endif/*end of file*/