#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(LOGGER);

int main(void)
{
	int exercise_num = 2;
	uint8_t data[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 'H', 'e', 'l', 'l','o'};
	// Printf-like messages
	LOG_INF("nRF Connect SDK Fundamentals");
	LOG_INF("Exercise %d",exercise_num);    
	LOG_DBG("A log message in debug level");
	LOG_WRN("A log message in warning level!");
	LOG_ERR("A log message in Error level!");
	// Hexdump some data
	LOG_HEXDUMP_INF(data, sizeof(data),"Sample Data!"); 
	return 0;
}
