#include "main.h"

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