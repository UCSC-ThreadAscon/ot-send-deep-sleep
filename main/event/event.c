#include "main.h"
#include "math.h"

/**
 * STEP 1: Segmentation
 * --------------------
 * Your experiments will run for 183 minutes, and you will need to send
 * "n" event packets, depending on the role the device is playing. Thus,
 * "n" is a value in {1, 10, 36}.
 *
 * Divide 183 minutes into "floor(183/n)" partitions. Then, for each partition,
 * find a RANDOM MINUTE (no seconds, or ms, or us) to have an event in.
 *
 * This method of segmentation will AVOID DUPLICATE events, when there are two
 * events that will be sent at the same time (or are really close).
*/

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