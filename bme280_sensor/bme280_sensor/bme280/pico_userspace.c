/**\
 * Copyright (c) 2020 Bosch Sensortec GmbH. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 **/

/**
 * \ingroup bme280
 * \defgroup bme280Examples Examples
 * @brief Reference Examples
 */

/*!
 * @ingroup bme280Examples
 * @defgroup bme280GroupExampleLU linux_userspace
 * @brief Linux userspace test code, simple and mose code directly from the doco.
 * compile like this: gcc linux_userspace.c ../bme280.c -I ../ -o bme280
 * tested: Raspberry Pi.
 * Use like: ./bme280 /dev/i2c-0
 * \include linux_userspace.c
 */

// @del
// =====>
#if 0
#ifdef __KERNEL__
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#endif
#endif
// <=====

/******************************************************************************/
/*!                         System header files                               */
// @del
// =====>
#if 0
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#endif
// <=====

/******************************************************************************/
/*!                         Own header files                                  */
#include "bme280_pico.h"

/******************************************************************************/
/*!                               Structures                                  */

// @del
// =====>
#if 0
/* Structure that contains identifier details used in example */
struct identifier
{
    /* Variable to hold device address */
    uint8_t dev_addr;

    /* Variable that contains file descriptor */
    int8_t fd;
};
#endif
// <=====

// @add
// =====>
struct bme280_dev dev = {0};
struct identifier id = {0};
// <=====

/****************************************************************************/
/*!                         Functions                                       */

/*!
 *  @brief Function that creates a mandatory delay required in some of the APIs.
 *
 * @param[in] period              : Delay in microseconds.
 * @param[in, out] intf_ptr       : Void pointer that can enable the linking of descriptors
 *                                  for interface related call backs
 *  @return void.
 *
 */
void user_delay_us(uint32_t period, void *intf_ptr);

/*!
 *  @brief Function for reading the sensor's registers through I2C bus.
 *
 *  @param[in] reg_addr       : Register address.
 *  @param[out] data          : Pointer to the data buffer to store the read data.
 *  @param[in] len            : No of bytes to read.
 *  @param[in, out] intf_ptr  : Void pointer that can enable the linking of descriptors
 *                                  for interface related call backs.
 *
 *  @return Status of execution
 *
 *  @retval 0 -> Success
 *  @retval > 0 -> Failure Info
 *
 */
int8_t user_i2c_read(uint8_t reg_addr, uint8_t *data, uint32_t len, void *intf_ptr);

/*!
 *  @brief Function for writing the sensor's registers through I2C bus.
 *
 *  @param[in] reg_addr       : Register address.
 *  @param[in] data           : Pointer to the data buffer whose value is to be written.
 *  @param[in] len            : No of bytes to write.
 *  @param[in, out] intf_ptr  : Void pointer that can enable the linking of descriptors
 *                                  for interface related call backs
 *
 *  @return Status of execution
 *
 *  @retval BME280_OK -> Success
 *  @retval BME280_E_COMM_FAIL -> Communication failure.
 *
 */
int8_t user_i2c_write(uint8_t reg_addr, const uint8_t *data, uint32_t len, void *intf_ptr);

/*!
 * @brief This function reading the sensor's registers through I2C bus.
 */
int8_t user_i2c_read(uint8_t reg_addr, uint8_t *data, uint32_t len, void *intf_ptr)
{
    struct identifier id;

    id = *((struct identifier *)intf_ptr);

    // @chg
    // =====>
#if 0
    write(id.fd, &reg_addr, 1);
    read(id.fd, data, len);
#endif
    if (1 != i2c_write_blocking(id.i2c, id.dev_addr, &reg_addr, 1, true)) {
        return BME280_E_COMM_FAIL;
    }
    if (len != i2c_read_blocking(id.i2c, id.dev_addr, data, len, false)) {
        return BME280_E_COMM_FAIL;
    }
    // <=====

    return 0;
}

/*!
 * @brief This function provides the delay for required time (Microseconds) as per the input provided in some of the
 * APIs
 */
void user_delay_us(uint32_t period, void *intf_ptr)
{
    // @chg
    // =====>
    //usleep(period);
    sleep_us(period);
    // <=====
}

/*!
 * @brief This function for writing the sensor's registers through I2C bus.
 */
int8_t user_i2c_write(uint8_t reg_addr, const uint8_t *data, uint32_t len, void *intf_ptr)
{
    uint8_t *buf;
    struct identifier id;

    id = *((struct identifier *)intf_ptr);

    buf = malloc(len + 1);
    buf[0] = reg_addr;
    memcpy(buf + 1, data, len);
    // @chg
    // =====>
    //if (write(id.fd, buf, len + 1) < (uint16_t)len)
    if ((len + 1) != i2c_write_blocking(id.i2c, id.dev_addr, buf, len + 1, false))
    // <=====
    {
        // @add
        // =====>
        free(buf);
        // <=====
        return BME280_E_COMM_FAIL;
    }

    free(buf);

    return BME280_OK;
}

// @add
// =====>
// Initialize pico dependent parts for BME280 API
struct bme280_dev* bme280_user_init(void)
{
    // [Initialize I2C]
    // SDA Pin
    gpio_init(BME280_USER_I2C_SDA);
    gpio_set_function(BME280_USER_I2C_SDA, GPIO_FUNC_I2C);
    gpio_pull_up(BME280_USER_I2C_SDA);
    // SCL Pin
    gpio_init(BME280_USER_I2C_SCL);
    gpio_set_function(BME280_USER_I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(BME280_USER_I2C_SCL);
    // clock frequency
    i2c_init(BME280_USER_I2C_ID, BME280_USER_I2C_FREQ);
          
    id.i2c = BME280_USER_I2C_ID;

    /* Make sure to select BME280_I2C_ADDR_PRIM or BME280_I2C_ADDR_SEC as needed */
    id.dev_addr = BME280_USER_SLAVE_ADDR;

    dev.intf = BME280_I2C_INTF;
    dev.read = user_i2c_read;
    dev.write = user_i2c_write;
    dev.delay_us = user_delay_us;

    /* Update interface pointer with the structure that contains both device address and file descriptor */
    dev.intf_ptr = &id;

    return &dev;
}