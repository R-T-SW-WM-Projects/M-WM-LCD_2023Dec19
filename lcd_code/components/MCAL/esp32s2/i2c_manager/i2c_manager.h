#ifndef _I2C_MANAGER_H
#define _I2C_MANAGER_H

#ifdef __cplusplus
extern "C" {
#endif



// Only here to get the I2C_NUM_0 and I2C_NUM_1 defines.
#include <driver/i2c.h>

#define I2C_ADDR_10 ( 1 << 15 )
#define I2C_REG_16  ( 1 << 31 )
#define I2C_NO_REG  ( 1 << 30 )

esp_err_t i2c_manager_init(i2c_port_t port);
esp_err_t i2c_manager_read(i2c_port_t port, uint16_t addr, uint32_t reg, uint8_t *buffer, uint16_t size);
esp_err_t i2c_manager_write(i2c_port_t port, uint16_t addr, uint32_t reg, const uint8_t *buffer, uint16_t size);
esp_err_t i2c_manager_close(i2c_port_t port);
esp_err_t i2c_manager_lock(i2c_port_t port);
esp_err_t i2c_manager_unlock(i2c_port_t port);
esp_err_t i2c_manager_force_unlock(i2c_port_t port);

    void* i2c_manager_locking();

    typedef struct {
        int32_t (* read)(void *handle, uint8_t address, uint8_t reg, uint8_t *buffer, uint16_t size);
        int32_t (* write)(void *handle, uint8_t address, uint8_t reg, const uint8_t *buffer, uint16_t size);
        void *handle;
    } i2c_hal_t;

    void* i2c_hal(i2c_port_t port);


#ifdef __cplusplus
}
#endif
#endif
