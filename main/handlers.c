#include "main.h"

void onPowerOn(struct timeval *events,
               nvs_handle_t *eventsHandle)
{
  initEventsArray(events, getCurrentTimeval(), getFutureTimeval(EXP_TIME_SECONDS));
  printEventsArray(events, NUM_EVENTS);

  openReadWrite(NVS_EVENTS_ARRAY, eventsHandle);
  return;
}