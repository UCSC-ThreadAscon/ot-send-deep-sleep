#include "time.h"

/**
 * The code to get the current time comes from the ESP-IDF documentatation:
 * https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/system/system_time.html
*/
int64_t getCurrentTime() {
struct timeval tv_now;
gettimeofday(&tv_now, NULL);
int64_t time_us = (int64_t)tv_now.tv_sec * 1000000L + (int64_t)tv_now.tv_usec;
return time_us;
}