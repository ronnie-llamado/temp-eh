#include <zephyr/kernel.h>

static uint32_t count = 0;

int main(void)
{
	while(1)
	{
		printk("Alive (%d)!\r\n", count++);
		k_sleep(K_SECONDS(1));
	}
}
