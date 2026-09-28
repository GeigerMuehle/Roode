// I2C-Schicht fuer die VL53L1X-ULD-Bibliothek ueber den ESPHome-I2C-Bus.
// Ersetzt die urspruengliche Arduino-Wire-Implementierung, die mit aktuellen
// ESPHome-Versionen nicht mehr funktioniert (Wire wird nie initialisiert).
#include "VL53L1X_i2ccoms.h"
#include "vl53l1_error_codes.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace vl53l1x {
// Wird in VL53L1X::setup() auf die Sensor-Instanz gesetzt.
i2c::I2CDevice *uld_i2c_device = nullptr;
}  // namespace vl53l1x
}  // namespace esphome

using esphome::vl53l1x::uld_i2c_device;

int8_t i2c_init() { return VL53L1_ERROR_NONE; }

// deviceAddress wird ignoriert: Die Adresse kommt aus der ESPHome-Config (0x29).
int8_t i2c_write_multi(uint8_t deviceAddress, uint16_t registerAddress, uint8_t *pdata, uint32_t count) {
  (void) deviceAddress;
  if (uld_i2c_device == nullptr)
    return VL53L1_ERROR_CONTROL_INTERFACE;
  auto err = uld_i2c_device->write_register16(registerAddress, pdata, count);
  return err == esphome::i2c::ERROR_OK ? VL53L1_ERROR_NONE : VL53L1_ERROR_CONTROL_INTERFACE;
}

int8_t i2c_read_multi(uint8_t deviceAddress, uint16_t registerAddress, uint8_t *pdata, uint32_t count) {
  (void) deviceAddress;
  if (uld_i2c_device == nullptr)
    return VL53L1_ERROR_CONTROL_INTERFACE;
  auto err = uld_i2c_device->read_register16(registerAddress, pdata, count);
  return err == esphome::i2c::ERROR_OK ? VL53L1_ERROR_NONE : VL53L1_ERROR_CONTROL_INTERFACE;
}

int8_t i2c_write_byte(uint8_t deviceAddress, uint16_t registerAddress, uint8_t data) {
  return i2c_write_multi(deviceAddress, registerAddress, &data, 1);
}

int8_t i2c_write_word(uint8_t deviceAddress, uint16_t registerAddress, uint16_t data) {
  uint8_t buff[2] = {(uint8_t) (data >> 8), (uint8_t) (data & 0xFF)};
  return i2c_write_multi(deviceAddress, registerAddress, buff, 2);
}

int8_t i2c_write_Dword(uint8_t deviceAddress, uint16_t registerAddress, uint32_t data) {
  uint8_t buff[4] = {(uint8_t) (data >> 24), (uint8_t) (data >> 16), (uint8_t) (data >> 8), (uint8_t) (data & 0xFF)};
  return i2c_write_multi(deviceAddress, registerAddress, buff, 4);
}

int8_t i2c_read_byte(uint8_t deviceAddress, uint16_t registerAddress, uint8_t *data) {
  return i2c_read_multi(deviceAddress, registerAddress, data, 1);
}

int8_t i2c_read_word(uint8_t deviceAddress, uint16_t registerAddress, uint16_t *data) {
  uint8_t buff[2] = {0, 0};
  int8_t r = i2c_read_multi(deviceAddress, registerAddress, buff, 2);
  *data = ((uint16_t) buff[0] << 8) | buff[1];
  return r;
}

int8_t i2c_read_Dword(uint8_t deviceAddress, uint16_t registerAddress, uint32_t *data) {
  uint8_t buff[4] = {0, 0, 0, 0};
  int8_t r = i2c_read_multi(deviceAddress, registerAddress, buff, 4);
  *data = ((uint32_t) buff[0] << 24) | ((uint32_t) buff[1] << 16) | ((uint32_t) buff[2] << 8) | buff[3];
  return r;
}
