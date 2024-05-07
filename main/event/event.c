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

void printEventsIndex(EventsIndex index)
{
  otLogNotePlat("Currently at event %" PRIu8 ".", index);
  return;
}

/**
 * Creates an event index which refers to the first event
 * in the events array, and then write this event index to NVS.
*/
EventsIndex initEventsIndex(nvs_handle_t handle)
{
  EventsIndex index = 0;
  nvsWriteByteUInt(handle, NVS_EVENTS_INDEX, index);
  return index;
}

EventsIndex readEventsIndex(nvs_handle_t handle)
{
  return nvsReadByteUInt(handle, NVS_EVENTS_INDEX);
}

void incEventsIndex(EventsIndex *indexPtr, nvs_handle_t handle)
{
  *indexPtr += 1;
  nvsWriteByteUInt(handle, NVS_EVENTS_INDEX, *indexPtr);
  return;
}