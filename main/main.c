#include "main.h"

/**
 * ---- TO-DO LIST ----
 *
 * 1. Get the device to go to deep sleep. Write code that can
 *    tell the difference between deep sleep wakeup, and being powered on.
*/

void app_main(void)
{
  initAppMain();

  struct timeval timevalNow = getCurrentTimeval(); 
  struct timeval timevalExpEnd = getFutureTimeval(EXP_TIME_SECONDS);

  struct timeval events[NUM_EVENTS];
  initEventsArray(events, timevalNow, timevalExpEnd);
  printEventsArray(events, NUM_EVENTS);

  initDeepSleepTimerMs(BATTERY_WAIT_TIME_MS);
  deepSleepStart();

  return;
}
