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
  checkConnection(esp_openthread_get_instance());

  struct timeval events[NUM_EVENTS];
  uuid deviceId;

  if (JUST_POWERED_ON)
  {
    onPowerOn(events, &deviceId);
  }
  else
  {
    onDeepSleepWakeup(events);
  }

  initDeepSleepTimerMs(BATTERY_WAIT_TIME_MS_TEST);
  deepSleepStart();
  return;
}
