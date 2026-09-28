/**
 * I2C-Schicht der VL53L1X-ULD-Bibliothek, angepasst fuer ESPHome:
 * Alle Zugriffe laufen ueber den I2C-Bus von ESPHome statt ueber Arduino Wire.
 */
#ifndef _VL53L1X_I2CCOMS_H_
#define _VL53L1X_I2CCOMS_H_

#include "vl53l1_types.h"

#ifdef __cplusplus
extern "C" {
#endif

int8_t i2c_init();
int8_t i2c_write_multi(uint8_t deviceAddress, uint16_t registerAddress, uint8_t *pdata, uint32_t count);
int8_t i2c_read_multi(uint8_t deviceAddress, uint16_t registerAddress, uint8_t *pdata, uint32_t count);
int8_t i2c_write_byte(uint8_t deviceAddress, uint16_t registerAddress, uint8_t data);
int8_t i2c_write_word(uint8_t deviceAddress, uint16_t registerAddress, uint16_t data);
int8_t i2c_write_Dword(uint8_t deviceAddress, uint16_t registerAddress, uint32_t data);
int8_t i2c_read_byte(uint8_t deviceAddress, uint16_t registerAddress, uint8_t *pdata);
int8_t i2c_read_word(uint8_t deviceAddress, uint16_t registerAddress, uint16_t *pdata);
int8_t i2c_read_Dword(uint8_t deviceAddress, uint16_t registerAddress, uint32_t *pdata);

#ifdef __cplusplus
}
#endif

#endif
