#ifndef _BME280_PICO_USERSPACE_H
#define _BME280_PICO_USERSPACE_H

// @add
// =====>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
// <=====

// I2C Config
#define BME280_USER_I2C_ID      i2c0         // i2c0 or i2c1
#define BME280_USER_I2C_SDA     8            // GP number of SDA pin
#define BME280_USER_I2C_SCL     9            // GP number of SCL pin
#define BME280_USER_I2C_FREQ    (100 * 1000) // clock frequency(Hz)

// [BME280 I2C slave address]
// Choose one of the following
// - BME280_I2C_ADDR_PRIM(0x76)
// - BME280_I2C_ADDR_SEC(0x77)
#define BME280_USER_SLAVE_ADDR  BME280_I2C_ADDR_PRIM 

struct identifier
{
    uint8_t     dev_addr;
    i2c_inst_t* i2c;
};

struct bme280_dev* bme280_user_init(void);

#endif
