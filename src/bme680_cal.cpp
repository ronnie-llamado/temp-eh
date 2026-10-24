
#include "bme680_cal.hpp"

namespace bme680 {

int16_t compensateTempInt(const temp_cal_t* cal, uint32_t rawTemp) {
  int32_t var1 = ((int32_t)rawTemp >> 3) - ((int32_t)cal->T1 << 1);
  int32_t var2 = (var1 * (int32_t)cal->T2) >> 11;
  int32_t var3 =
      ((((var1 >> 1) * (var1 >> 1)) >> 12) * ((int32_t)cal->T3 << 4)) >> 14;
  int32_t t_fine = var2 + var3;
  return (((t_fine * 5) + 128) >> 8);
}

}  // namespace bme680
