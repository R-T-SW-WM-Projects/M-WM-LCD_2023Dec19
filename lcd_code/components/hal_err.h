#ifndef HAL_ERR_H
#define HAL_ERR_H

#include "../MCAL/mcal.h"

#define HAL_ERROR_CHECK(fun, __expected, _return)            \
    do{                                                      \
        driver_err_t __err_rc = (fun);                        \
        if (__err_rc != __expected) {                        \
            return _return;                                  \
        }                                                    \
    } while(0)


typedef int16_t hal_err_t;

#define HAL_OK                    (0)
#define HAL_FAIL                  (-1)
#define HAL_TIMEOUT               (0x02)
#define HAL_INVALID_VAL           (0x03)
#define HAL_NOT_READY             (0x04)
#define HAL_OVERFLOW              (0x05)
#define HAL_ERR_INVALID_ARG       (0x06)

#define INVERTER_BASE        (0x80)
#define HAL_RX               (0x01+INVERTER_BASE)
#define HAL_FOD              (0x02+INVERTER_BASE)
#define HAL_SEMI_FOD         (0x03+INVERTER_BASE)
#define HAL_VOLT_SET         (0x04+INVERTER_BASE)
#define HAL_VOLT_HIGHER      (0x05+INVERTER_BASE)
#define HAL_VOLT_LOWER       (0x06+INVERTER_BASE)
#define HAL_FAIL_COIL        (0x07+INVERTER_BASE)
#define HAL_FAIL_RX          (0x08+INVERTER_BASE)
//
#define HAL_COMM_BASE             0x40
#define HAL_ADDR_NACK         (HAL_COMM_BASE+0x01)


#endif