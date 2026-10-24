
#include "zephyr_i2c.hpp"

#include <zephyr/drivers/i2c.h>

int ZephyrI2cBus::read(uint8_t addr, uint8_t* rx, size_t len) {
  return i2c_read(dev_, rx, len, addr);
}

int ZephyrI2cBus::write(uint8_t addr, const uint8_t* tx, size_t len) {
  return i2c_write(dev_, tx, len, addr);
}

int ZephyrI2cBus::writeRead(
    uint8_t addr, const uint8_t* tx, size_t txLen, uint8_t* rx, size_t rxLen) {
  return i2c_write_read(dev_, addr, tx, txLen, rx, rxLen);
}
