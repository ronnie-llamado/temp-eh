#pragma once

#include <stdint.h>

namespace bme680 {

struct temp_cal_t {
  uint16_t T1;
  uint16_t T2;
  uint8_t T3;
};

int16_t compensateTempInt(const temp_cal_t* cal, uint32_t rawTemp);

}  // namespace bme680
