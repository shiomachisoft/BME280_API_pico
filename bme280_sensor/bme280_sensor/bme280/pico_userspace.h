#ifndef _BME280_PICO_USERSPACE_H
#define _BME280_PICO_USERSPACE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"

struct identifier
{
    uint8_t     dev_addr;
    i2c_inst_t* i2c;
};

struct bme280_dev* bme280_user_init(void);

#endif
