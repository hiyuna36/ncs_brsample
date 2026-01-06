#include <zephyr/kernel.h>

int main(void)
{
	printf("Hello World! %s\n", CONFIG_BOARD_TARGET);
	printk("Hello World! %s\n", CONFIG_BOARD_TARGET);
	return 0;
}
