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

 private:
  T& t_;
};
