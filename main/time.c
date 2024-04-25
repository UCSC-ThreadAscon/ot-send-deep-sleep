/**
 * All of the code in the documention is both taken from and based upon the code
 * from the "System Time" page from the ESP-IDF documentation:
 * https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/system/system_time.html
*/

#include "time.h"

int64_t timevalToMicro(struct timeval time) {
  return (int64_t)time.tv_sec * 1000000L + (int64_t)time.tv_usec;
}

int64_t getCurrentTime()
{
  struct timeval tvNow;
  gettimeofday(&tvNow, NULL);
  return timevalToMicro(tvNow);
}

/**
 * What will be the timestamp if if it is "x" seconds from now?
*/
struct timeval getFutureTimeval(int64_t seconds) {
  struct timeval tvFuture;
  gettimeofday(&tvFuture, NULL);
  tvFuture.tv_sec += seconds;
  return tvFuture;
}