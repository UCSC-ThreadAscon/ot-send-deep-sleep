#include "utilities.h"
#include "workload.h"
#include "init.h"
#include "time.h"

void app_main(void)
{
  initAppMain();

  struct timeval tvNow = getCurrentTimeval(); 
  struct timeval tvExp = getFutureTimeval(EXP_TIME_SECONDS);

  int64_t eventsUs[NUM_EVENTS_TEST];
  EmptyMemory(eventsUs, sizeof(eventsUs));

    for (int i = 0; i < NUM_EVENTS_TEST; i++) {
      struct timeval tvRandom = randomTime(tvNow, tvExp);
      int64_t randomTimeMicro = timevalToMicro(tvRandom);
      eventsUs[i] = randomTimeMicro;
    }

    qsort(&eventsUs, NUM_EVENTS_TEST, sizeof(int64_t), compare);

    for (int i = 0; i < NUM_EVENTS_TEST; i++) {
      otLogNotePlat("The next event will be in approximately %" PRId64 " minutes.",
                    US_TO_MINUTES(eventsUs[i]));
    }

    return;
}
