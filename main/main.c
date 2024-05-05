#include "utilities.h"
#include "workload.h"
#include "init.h"
#include "time.h"
#include "sleep.h"

#define NUM_EVENTS NUM_EVENTS_AIR_MONITOR

void initEventsArray(struct timeval *events,
                     struct timeval start,
                     struct timeval end)
{
  for (int i = 0; i < NUM_EVENTS; i++)
  {
    events[i] = randomTime(start, end);
  }

  qsort(events, NUM_EVENTS, sizeof(struct timeval), compareTimevals);
  return;
}

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
