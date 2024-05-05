#include "main.h"

void onPowerOn(struct timeval *events)
{
  nvs_handle_t handle;
  openReadWrite(NVS_NAMESPACE, &handle);

  initEventsArray(events, getCurrentTimeval(), getFutureTimeval(EXP_TIME_SECONDS));
  printEventsArray(events, NUM_EVENTS);

  writeTimevalArray(&handle, NVS_EVENTS_ARRAY, events, EVENTS_ARRAY_SIZE);

  nvs_close(handle);
  return;
}

void onDeepSleepWakeup(struct timeval *events)
{
  nvs_handle_t handle;
  openReadWrite(NVS_NAMESPACE, &handle);

  readTimevalArray(&handle, NVS_EVENTS_ARRAY, events, EVENTS_ARRAY_SIZE);
  printEventsArray(events, NUM_EVENTS);

  nvs_close(handle);
  return;
}