#pragma once

#include <stdint.h>

#include "bme680_cal.hpp"

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

struct Mode {
  using Type = uint8_t;

  static constexpr Type SLEEP = 0;
  static constexpr Type FORCED = 1;
};

struct OsrsTemp {
  using Type = uint8_t;

  static constexpr Type SKIPPED = 0 << 5;
  static constexpr Type X1 = 1 << 5;
  static constexpr Type X2 = 2 << 5;
  static constexpr Type X4 = 3 << 5;
  static constexpr Type X8 = 4 << 5;
  static constexpr Type X16 = 5 << 5;
};

template <typename Bus>
class Bme680 {
 public:
  explicit Bme680(Bus& bus, uint8_t addr) : bus_(bus), addr_(addr) {}

  int configureTempOsr(OsrsTemp::Type osr);
  int readTempCal1(void);
  int readTempCal2(void);
  int readTempCal3(void);
  int readChipId(uint8_t* chipId);
  int readTempInt(int16_t* temp);
  int triggerMeasurement(void);

 protected:
  int readRawTemp(uint32_t* rawTemp);

 private:
  Bus& bus_;
  uint8_t addr_;

  bme680::temp_cal_t temp_cal_;

  OsrsTemp::Type osrs_temp_ = OsrsTemp::SKIPPED;
};

template <typename Bus>
int Bme680<Bus>::configureTempOsr(OsrsTemp::Type osr) {
  osrs_temp_ = osr;
  return 0;
}

template <typename Bus>
int Bme680<Bus>::readTempCal1(void) {
  return bus_.readRegister16(addr_, T1_LSB, &temp_cal_.T1);
}

template <typename Bus>
int Bme680<Bus>::readTempCal2(void) {
  return bus_.readRegister16(addr_, T2_LSB, &temp_cal_.T2);
}

template <typename Bus>
int Bme680<Bus>::readTempCal3(void) {
  return bus_.readRegister8(addr_, T3, &temp_cal_.T3);
}

template <typename Bus>
int Bme680<Bus>::readChipId(uint8_t* chipId) {
  return bus_.readRegister8(addr_, CHIP_ID, chipId);
}

template <typename Bus>
int Bme680<Bus>::readRawTemp(uint32_t* rawTemp) {
  uint8_t raw[3];

  bus_.readRegister(addr_, TEMP_MSB, &raw[0], 3);
  *rawTemp = (raw[0] << 12) + (raw[1] << 4) + (raw[2] >> 4);

  return 0;
}

template <typename Bus>
int Bme680<Bus>::readTempInt(int16_t* temp) {
  uint32_t rawTemp = 0;

  readRawTemp(&rawTemp);
  *temp = bme680::compensateTempInt(&temp_cal_, rawTemp);

  return 0;
}

template <typename Bus>
int Bme680<Bus>::triggerMeasurement(void) {
  uint8_t data = (uint8_t)(osrs_temp_ | Mode::FORCED);
  return bus_.writeRegister8(addr_, CTRL_MEAS, data);
}
