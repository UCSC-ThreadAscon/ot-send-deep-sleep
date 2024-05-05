#include "utilities.h"
#include "workload.h"
#include "init.h"
#include "time.h"

void app_main(void)
{
  initAppMain();

  struct timeval timevalNow = getCurrentTimeval(); 
  struct timeval timevalExpEnd = getFutureTimeval(EXP_TIME_SECONDS);

  struct timeval events[NUM_EVENTS_AIR_MONITOR];

  for (int i = 0; i < NUM_EVENTS_AIR_MONITOR; i++)
  {
    events[i] = randomTime(timevalNow, timevalExpEnd);

    // Print time in minutes for debugging.
    int64_t timeMicro = timevalToMicro(events[i]);
    int64_t timeMinutes = US_TO_MINUTES(timeMicro);
    otLogNotePlat("The %dth event will be in %" PRId64 " minutes.",
                  i, timeMinutes);
  }


  // int64_t eventsUs[NUM_EVENTS_AIR_MONITOR];
  // EmptyMemory(eventsUs, sizeof(eventsUs));

  //   for (int i = 0; i < NUM_EVENTS_AIR_MONITOR; i++) {
  //     struct timeval tvRandom = randomTime(tvNow, tvExp);
  //     int64_t randomTimeMicro = timevalToMicro(tvRandom);
  //     eventsUs[i] = randomTimeMicro;
  //   }

  //   qsort(&eventsUs, NUM_EVENTS_AIR_MONITOR, sizeof(int64_t), compare);

  //   for (int i = 0; i < NUM_EVENTS_AIR_MONITOR; i++) {
  //     otLogNotePlat("The next event will be in approximately %" PRId64 " minutes.",
  //                   US_TO_MINUTES(eventsUs[i]));
  //   }

    return;
}
