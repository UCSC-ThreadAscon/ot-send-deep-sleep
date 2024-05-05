#include "main.h"

/**
 * ---- CURRENT TO-DO ----
 * Store EVERYTHING in NVS on power on. Then on wakeup, get everything
 * from NVS and print it out.
*/

#define BATTERY_WAIT_TIME_MS_TEST 5000

void app_main(void)
{
  initAppMain();

  struct timeval events[NUM_EVENTS];
  nvs_handle_t eventsHandle;

  if (JUST_POWERED_ON)
  {
    onPowerOn(events, &eventsHandle);
  }
  else
  {
    otLogNotePlat("I just woke up from deep sleep!");
  }

  initDeepSleepTimerMs(BATTERY_WAIT_TIME_MS_TEST);
  deepSleepStart();
  return;
}
