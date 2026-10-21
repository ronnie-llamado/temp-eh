
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/sensor_data_types.h>
#include <zephyr/rtio/rtio.h>
#include <zephyr/dsp/print_format.h>

#define TEMPERATURE_STACK_SIZE	1024
#define TEMPERATURE_PRIORITY	4

static void temperature_thread(void *p1, void *p2, void *p3)
{
	ARG_UNUSED(p1);
	ARG_UNUSED(p2);
	ARG_UNUSED(p3);

	const struct device *const dev = DEVICE_DT_GET_ONE(bosch_bme680);
	struct sensor_value temp, press, humidity, gas_res;

	if (!device_is_ready(dev)) {
		printk("sensor: device not ready.\n");
		return;
	}

	printk("Device %p name is %s\n", dev, dev->name);

	while (1) {
		k_sleep(K_MSEC(3000));

		sensor_sample_fetch(dev);
		sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &temp);
		sensor_channel_get(dev, SENSOR_CHAN_PRESS, &press);
		sensor_channel_get(dev, SENSOR_CHAN_HUMIDITY, &humidity);
		sensor_channel_get(dev, SENSOR_CHAN_GAS_RES, &gas_res);

		printk("T: %d.%06d; P: %d.%06d; H: %d.%06d; G: %d.%06d\n",
				temp.val1, temp.val2, press.val1, press.val2,
				humidity.val1, humidity.val2, gas_res.val1,
				gas_res.val2);
	}

	return;
}

K_THREAD_DEFINE(temperature_tid, TEMPERATURE_STACK_SIZE, temperature_thread, NULL, NULL, NULL, TEMPERATURE_PRIORITY, 0, 0);

