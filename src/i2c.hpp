#pragma once

#include <stdint.h>
#include <stdlib.h>

template <typename T>
class I2cBus {
 public:
  explicit I2cBus(T& t) : t_(t) {}

  int read(uint8_t addr, uint8_t* rx, size_t len) {
    return t_.read(addr, rx, len);
  }

  int write(uint8_t addr, const uint8_t* tx, size_t len) {
    return t_.write(addr, tx, len);
  }

  int writeRead(uint8_t addr,
                const uint8_t* tx,
                size_t txLen,
                uint8_t* rx,
                size_t rxLen) {
    return t_.writeRead(addr, tx, txLen, rx, rxLen);
  }

  // Register Helpers
  int readRegister(uint8_t addr, uint8_t reg, uint8_t* rx, size_t len)
  {
    return writeRead(addr, &reg, 1, rx, len);
  }

  int readRegister8(uint8_t addr, uint8_t reg, uint8_t *data)
  {
    return writeRead(addr, &reg, 1, data, 1);
  }

  int readRegister16(uint8_t addr, uint8_t reg, uint16_t *data)
  {
    uint8_t rx[2];
    writeRead(addr, &reg, 1, &rx[0], 2);
    *data = (rx[1] << 8) + rx[0];
    return 0;
  }

  int writeRegister8(uint8_t addr, uint8_t reg, uint8_t data)
  {
    uint8_t tx[2] = { reg, data };
    return write(addr, &tx[0], 2);
  }

 private:
  T& t_;
};
