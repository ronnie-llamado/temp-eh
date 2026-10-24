
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include "bme680.hpp"
#include "i2c.hpp"
#include "zephyr_i2c.hpp"

#define LED0_NODE DT_ALIAS(led0)

static const struct device* const i2c = DEVICE_DT_GET(DT_NODELABEL(i2c21));
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

int main(void) {
  int ret;
  int16_t temp;

  ZephyrI2cBus zephyrI2cBus(i2c);
  I2cBus<ZephyrI2cBus> i2cBus(zephyrI2cBus);
  Bme680<I2cBus<ZephyrI2cBus>> bme680(i2cBus, 0x76);

  if (!gpio_is_ready_dt(&led)) {
    return 1;
  }

  ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
  if (ret < 0) {
    return 1;
  }

  // Initialize BME680
  bme680.readTempCal1();
  bme680.readTempCal2();
  bme680.readTempCal3();
  bme680.configureTempOsr(OsrsTemp::X16);

  while (1) {
    // Read temperature
    bme680.readTempInt(&temp);
    printk("%d.%02d\r\n", temp / 100, abs(temp % 100));

    // Toggle LED
    ret = gpio_pin_toggle_dt(&led);
    if (ret < 0) {
      return 1;
    }

    // Trigger next measurement
    bme680.triggerMeasurement();

    k_sleep(K_MSEC(500));
  }

  return 0;
}
