#include "main.h"

void app_main(void)
{
  initAppMain();

  struct timeval timevalNow = getCurrentTimeval(); 
  struct timeval timevalExpEnd = getFutureTimeval(EXP_TIME_SECONDS);

  struct timeval events[NUM_EVENTS];
  initEventsArray(events, timevalNow, timevalExpEnd);
  printEventsArray(events, NUM_EVENTS);

  return;
}
