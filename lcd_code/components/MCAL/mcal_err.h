#ifndef MCAL_ERR_H
#define MCAL_ERR_H

#include "mcal.h"

#define MCAL_ERROR_CHECK(fun, __expected, _return)            \
    do{                                                      \
        mcal_err_t __err_rc = (fun);                        \
        if (__err_rc != __expected) {                        \
            return _return;                                  \
        }                                                    \
    } while(0)


typedef int16_t mcal_err_t;

#define MCAL_OK                    (0)
#define MCAL_FAIL                  (-1)
#define MCAL_TIMEOUT               (0x02)
#define MCAL_INVALID_VAL           (0x03)
#define MCAL_NOT_READY             (0x04)
#define MCAL_OVERFLOW              (0x05)
#define MCAL_ERR_INVALID_ARG       (0x06)


//
#define COMM_BASE              (0x40)
#define MCAL_ADDR_NACK         (COMM_BASE+0x01)


#endif