#include "utilities.h"
#include "workload.h"
#include "init.h"
#include "time.h"

#define NUM_EVENTS NUM_EVENTS_AIR_MONITOR

void app_main(void)
{
  initAppMain();

  struct timeval timevalNow = getCurrentTimeval(); 
  struct timeval timevalExpEnd = getFutureTimeval(EXP_TIME_SECONDS);

  struct timeval events[NUM_EVENTS];

  for (int i = 0; i < NUM_EVENTS; i++)
  {
    events[i] = randomTime(timevalNow, timevalExpEnd);
  }

  qsort(&events, NUM_EVENTS, sizeof(struct timeval), compareTimevals);
  printEventsArray(&events, NUM_EVENTS);

  return;
}
