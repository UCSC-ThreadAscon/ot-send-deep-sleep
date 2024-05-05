#include "main.h"

void onPowerOn(struct timeval *events)
{
  nvs_handle_t handle;
  openReadWrite(NVS_NAMESPACE, &handle);

  initEventsArray(events, getCurrentTimeval(), getFutureTimeval(EXP_TIME_SECONDS));
  printEventsArray(events, NUM_EVENTS);

  writeTimevalArray(&handle, NVS_EVENTS_ARRAY, events, sizeof(events));

  nvs_close(handle);
  return;
}

void onDeepSleepWakeup(struct timeval *events) {
  nvs_handle_t handle;
  openReadWrite(NVS_NAMESPACE, &handle);

  otLogNotePlat("I just woke up from deep sleep!");

  nvs_close(handle);
  return;
}