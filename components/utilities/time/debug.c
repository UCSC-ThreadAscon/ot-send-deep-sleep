#include "time.h"

void printEventMinutes(int eventNum, struct timeval time)
{
  int64_t timeMicro = toMicro(time);
  double timeMinutes = US_TO_MINUTES((double) timeMicro);
  otLogNotePlat("The %dth event will be in %.3f minutes.",
                eventNum, timeMinutes);
  return;
}

void printEventsArray(struct timeval *events, int numEvents) {
  for (int i = 0; i < numEvents; i++)
  {
    printEventMinutes(i + 1, events[i]);
  }
  return;
}