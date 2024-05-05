#include "time.h"

void printEventMinutes(int eventNum, struct timeval time)
{
  int64_t timeMicro = timevalToMicro(time);
  int64_t timeMinutes = US_TO_MINUTES(timeMicro);
  otLogNotePlat("The %dth event will be in %" PRId64 " minutes.",
                eventNum, timeMinutes);
  return;
}