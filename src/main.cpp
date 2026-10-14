#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define ALIVE_STACK_SIZE	1024
#define ALIVE_PRIORITY		5

static void alive_thread(void *p1, void *p2, void *p3)
{
	ARG_UNUSED(p1);
	ARG_UNUSED(p2);
	ARG_UNUSED(p3);

	static uint32_t count = 0;

	while(1)
	{
		printk("Alive (%d)!\r\n", count++);
		k_sleep(K_SECONDS(1));
	}
}

K_THREAD_DEFINE(alive_tid, ALIVE_STACK_SIZE, alive_thread, NULL, NULL, NULL, ALIVE_PRIORITY, 0, 0);

int main(void)
{
	return 0;
}
