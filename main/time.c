/**
 * All of the code in the documention is both taken from and based upon the code
 * from the "System Time" page from the ESP-IDF documentation:
 * https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/system/system_time.html
*/

#include "time.h"

inline int64_t timevalToMicro(struct timeval time) {
  return (int64_t)time.tv_sec * 1000000L + (int64_t)time.tv_usec;
}

int64_t getCurrentTime()
{
  struct timeval tvNow;
  gettimeofday(&tvNow, NULL);
  return timevalToMicro(tvNow);
}