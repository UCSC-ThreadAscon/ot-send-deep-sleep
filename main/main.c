#include "main.h"

#define BATTERY_WAIT_TIME_MS_TEST 5000

/**
 * ---- TO-DO LIST ----
 *
 * 1. Get the device to go to deep sleep. Write code that can
 *    tell the difference between deep sleep wakeup, and being powered on.
*/

#define JUST_POWERED_ON !isDeepSleepWakeup()

void onPowerOn(struct timeval *events) {
  struct timeval timevalNow = getCurrentTimeval(); 
  struct timeval timevalExpEnd = getFutureTimeval(EXP_TIME_SECONDS);

  initEventsArray(events, timevalNow, timevalExpEnd);
  printEventsArray(events, NUM_EVENTS);
  return;
}

void app_main(void)
{
  initAppMain();

  struct timeval events[NUM_EVENTS];

  if (JUST_POWERED_ON)
  {
    onPowerOn(events);
  }
  else
  {
    otLogNotePlat("I just woke up from deep sleep!");
  }

  initDeepSleepTimerMs(BATTERY_WAIT_TIME_MS_TEST);
  deepSleepStart();
  return;
}
