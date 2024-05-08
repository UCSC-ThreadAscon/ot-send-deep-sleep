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

void printEventsIndex(uint8_t index)
{
  otLogNotePlat("Events index is at %" PRIu8 ".", index);
  return;
}

void printEventsArray(struct timeval *events, int numEvents) {
  for (int i = 0; i < numEvents; i++)
  {
    printEventMinutes(i + 1, events[i]);
  }
  return;
}

void printEventMinutes(int eventNum, struct timeval time)
{
  uint64_t timeMicro = toMicro(time);
  double timeMinutes = US_TO_MINUTES((double) timeMicro);
  otLogNotePlat("The %dth event will be in %.3f minutes.",
                eventNum, timeMinutes);
  return;
}