#include "bme280/bme280_pico.h"

int8_t stream_sensor_data_forced_mode(struct bme280_dev *dev);
void print_sensor_data(struct bme280_data *comp_data);

int main()
{ 
    struct bme280_dev *dev = NULL;
    int8_t rslt = BME280_OK;

    // Initialize USB
    stdio_init_all();

    // Initialize pico dependent parts for BME280 API 
    dev = bme280_user_init();

    /* Initialize the bme280 */
    rslt = bme280_init(dev);
    if (rslt != BME280_OK)
    {
        printf("Failed to initialize the device (code %+d).\n", rslt);
        goto __end;
    }

    /* read the sensor temperature, pressure and humidity data in forced mode */
    rslt = stream_sensor_data_forced_mode(dev);
    if (rslt != BME280_OK)
    {
        printf("Failed to stream sensor data (code %+d).\n", rslt);
        goto __end;
    }

__end:
    return 0;
}

/*!
 * @brief This API reads the sensor temperature, pressure and humidity data in forced mode.
 */
int8_t stream_sensor_data_forced_mode(struct bme280_dev *dev)
{
    /* Variable to define the result */
    int8_t rslt = BME280_OK;

    /* Structure to store the settings */
    struct bme280_settings settings = {0};

    /* Variable to store minimum wait time between consecutive measurement in force mode */
    uint32_t req_delay;

    /* Structure to get the pressure, temperature and humidity values */
    struct bme280_data comp_data;

    /* Get the current sensor settings */
    rslt = bme280_get_sensor_settings(&settings, dev);
    if (rslt != BME280_OK)
    {
        printf("Failed to get sensor settings (code %+d).", rslt);

        return rslt;
    }

    /* Recommended mode of operation: Indoor navigation */
    settings.filter = BME280_FILTER_COEFF_16;
    settings.osr_h = BME280_OVERSAMPLING_1X;
    settings.osr_p = BME280_OVERSAMPLING_16X;
    settings.osr_t = BME280_OVERSAMPLING_2X;

    /* Set the sensor settings */
    rslt = bme280_set_sensor_settings(BME280_SEL_ALL_SETTINGS, &settings, dev);
    if (rslt != BME280_OK)
    {
        printf("Failed to set sensor settings (code %+d).", rslt);

        return rslt;
    }

    printf("Temperature, Pressure, Humidity\n");

    /*Calculate the minimum delay required between consecutive measurement based upon the sensor enabled
     *  and the oversampling configuration. */
    bme280_cal_meas_delay(&req_delay, &settings);

    /* Continuously stream sensor data */
    while (1)
    {
        /* Set the sensor to forced mode */
        rslt = bme280_set_sensor_mode(BME280_POWERMODE_FORCED, dev);
        if (rslt != BME280_OK)
        {
            printf("Failed to set sensor mode (code %+d).", rslt);
            break;
        }

        /* Wait for the measurement to complete and print data */
        dev->delay_us(req_delay, dev->intf_ptr);
        rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, dev);
        if (rslt != BME280_OK)
        {
            printf("Failed to get sensor data (code %+d).", rslt);
            break;
        }

        print_sensor_data(&comp_data);
    }

    return rslt;
}

/*!
 * @brief This API used to print the sensor temperature, pressure and humidity data.
 */
void print_sensor_data(struct bme280_data *comp_data)
{
    float temp, press, hum;

    temp = comp_data->temperature;
    press = 0.01 * comp_data->pressure;
    hum = comp_data->humidity;
    printf("%0.2lf deg C, %0.2lf hPa, %0.2lf%%\n", temp, press, hum);
}