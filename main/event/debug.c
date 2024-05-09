#include "main.h"

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
  otLogNotePlat("The %dth event will be in %.3f minutes from events init.",
                eventNum, timeMinutes);
  return;
}