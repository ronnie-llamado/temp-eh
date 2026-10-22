#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <zephyr/device.h>

class ZephyrI2cBus {
 public:
  explicit ZephyrI2cBus(const struct device* dev) : dev_(dev) {}

  int read(uint8_t addr, uint8_t* rx, size_t len);
  int write(uint8_t addr, const uint8_t* tx, size_t len);
  int writeRead(
      uint8_t addr, const uint8_t* tx, size_t txLen, uint8_t* rx, size_t rxLen);

 private:
  const struct device* dev_;
};
