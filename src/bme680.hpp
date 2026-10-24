#pragma once

#include <stdint.h>

constexpr uint8_t TEMP_MSB = 0x22;
constexpr uint8_t TEMP_LSB = 0x23;
constexpr uint8_t TEMP_XLSB = 0x24;
constexpr uint8_t CTRL_MEAS = 0x74;
constexpr uint8_t T2_LSB = 0x8A;
constexpr uint8_t T2_MSB = 0x8B;
constexpr uint8_t T3 = 0x8C;
constexpr uint8_t CHIP_ID = 0xD0;
constexpr uint8_t T1_LSB = 0xE9;
constexpr uint8_t T1_MSB = 0xEA;

template <typename Bus>
class Bme680 {
 public:
  explicit Bme680(Bus& bus, uint8_t addr) : bus_(bus), addr_(addr) {}

  int readTempCal(void);
  int readChipId(uint8_t* chipId);
  int readTemp(int16_t* temp);

 private:
  Bus& bus_;
  uint8_t addr_;
  uint16_t t1_;
  uint16_t t2_;
  uint8_t t3_;
};

template <typename Bus>
int Bme680<Bus>::readTempCal(void) {
  uint8_t regId;
  uint8_t data[2];

  regId = T1_LSB;
  bus_.writeRead(addr_, &regId, 1, &data[0], 2);
  t1_ = (data[1] << 8) + data[0];

  regId = T2_LSB;
  bus_.writeRead(addr_, &regId, 1, &data[0], 2);
  t2_ = (data[1] << 8) + data[0];

  regId = T3;
  bus_.writeRead(addr_, &regId, 1, &data[0], 1);
  t3_ = data[0];

  return 0;
}

template <typename Bus>
int Bme680<Bus>::readChipId(uint8_t* chipId) {
  const uint8_t regId = CHIP_ID;

  return bus_.writeRead(addr_, &regId, 1, chipId, 1);
}

template <typename Bus>
int Bme680<Bus>::readTemp(int16_t* temp) {
  uint8_t raw[3];

  // Enable forced mode, temperature OSR=1
  const uint8_t enableData[2] = {CTRL_MEAS, 0x21};
  bus_.write(addr_, &enableData[0], 2);

  // Read temperature adc
  const uint8_t regId = TEMP_MSB;
  uint32_t temp_adc = 0;
  bus_.writeRead(addr_, &regId, 1, &raw[0], 3);
  temp_adc = (raw[0] << 12) + (raw[1] << 4) + (raw[2] >> 4);

  // Apply temperature compensation (integer)
  int32_t var1;
  int32_t var2;
  int32_t var3;
  int32_t t_fine;

  var1 = ((int32_t)temp_adc >> 3) - ((int32_t)t1_ << 1);
  var2 = (var1 * (int32_t)t2_) >> 11;
  var3 = ((((var1 >> 1) * (var1 >> 1)) >> 12) * ((int32_t)t3_ << 4)) >> 14;
  t_fine = var2 + var3;
  *temp = ((t_fine * 5) + 128) >> 8;

  return 0;
}
