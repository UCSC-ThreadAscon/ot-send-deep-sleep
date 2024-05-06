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

/**
 * Creates the event number which starts at the first event
 * in the events array, and then write the events number to NVS.
*/
EventsIndex initEventsIndex() {
  EventsIndex eventsIndex = 0;
  return eventsIndex;
}