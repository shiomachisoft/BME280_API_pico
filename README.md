English website:  
https://sites.google.com/view/shiomachisoft/english-home  
Japanese website:  
https://sites.google.com/view/shiomachisoft/%E3%83%9B%E3%83%BC%E3%83%A0  
  
Bosch's BME280_SensorAPI was ported to Raspberry Pi Pico.(using C and pico-sdk, I2C)  
Version:BME280_SensorAPI-bme280_v3.5.1  
  
**1.How to use**  
  
Please set the following user-dependent settings in bme280_pico.h  

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
  
  
**2.In your app, do the following**  
  (See sample_main.c)  
  
(1) include "bme280/bme280_pico.h"  

(2) Pass the return value of bme280_user_init() to bme280_init().  

(3) Now you can use the Bosch API.  

(4) The list of Bosch API functions is in bme280.h.    
  
**3.Execution result of sample_main.c.**  
  
![image](https://github.com/shiomachisoft/BME280_API_pico/assets/172953847/daba6c32-7da9-486e-b786-7eaba6f6c6fa)

**4.license**    
  
Please check the Bosch's repository.  
https://github.com/boschsensortec/BME280_SensorAPI
