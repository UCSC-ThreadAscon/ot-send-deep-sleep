#include "main.h"

void onPowerOn(struct timeval *events)
{
  nvs_handle_t handle;

  initEventsArray(events, getCurrentTimeval(), getFutureTimeval(EXP_TIME_SECONDS));
  printEventsArray(events, NUM_EVENTS);

  openReadWrite(NVS_NAMESPACE, &handle);

  writeTimevalArray(&handle, NVS_EVENTS_ARRAY, events, sizeof(events));

  nvs_close(handle);
  return;
}