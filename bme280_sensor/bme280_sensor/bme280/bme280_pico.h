#ifndef _BME280_PICO_H
#define _BME280_PICO_H

#include "bme280.h"
#include "pico_userspace.h"

// [pico I2C config]
#define BME280_USER_I2C_ID      i2c0         // i2c0 or i2c1
#define BME280_USER_I2C_SDA     8            // GP number of SDA pin
#define BME280_USER_I2C_SCL     9            // GP number of SCL pin
#define BME280_USER_I2C_FREQ    (100 * 1000) // clock frequency(Hz)

// [BME280 I2C slave address]
// Choose one of the following
// - BME280_I2C_ADDR_PRIM(0x76)
// - BME280_I2C_ADDR_SEC(0x77)
#define BME280_USER_SLAVE_ADDR  BME280_I2C_ADDR_PRIM 

#endif