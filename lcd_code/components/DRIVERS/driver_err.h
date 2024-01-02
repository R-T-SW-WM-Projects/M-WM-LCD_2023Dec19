/* 
 * File:   dspic_err.h
 * Author: ASHRAF
 *
 * Created on 30 ????, 2021, 02:53 ?
 */

#ifndef DRIVER_ERR_H
#define	DRIVER_ERR_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdint.h>
/**********************
 *      TYPEDEFS
 **********************/
typedef int16_t driver_err_t;

/* Definitions for error constants. */
#define DRIVER_OK            0       /*!< driver_err_t value indicating success (no error) */
#define DRIVER_FAIL          -1      /*!< Generic driver_err_t code indicating failure */
#define DRIVER_TIMEOUT       2
#define DRIVER_INVALID_ARG   3


#define UART_BASE            0x40
#define DRIVER_FRAME_ERR     (0x01+UART_BASE)
#define DRIVER_PARITY_ERR    (0x02+UART_BASE)
#define DRIVER_OVER_FLOW     (0x03+UART_BASE)

#define I2C_BASE             0x30
#define DRIVER_NOT_ACK       (0x01+I2C_BASE)


#ifdef	__cplusplus
}
#endif

#endif	/* DSPIC_ERR_H */

