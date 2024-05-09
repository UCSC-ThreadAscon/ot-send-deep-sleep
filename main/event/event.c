#include "main.h"
#include "math.h"
/*
 * Segmentation Helper Function:       |-----------|
 * Choose a time in [i, j)             i     ^     j
 *                                           |
 *                                           |
 *                                           R
 *
 * where the random event R = r (mod (j - i)) + i
 * and where              r = esp_random();
 */
struct timeval segmentHelper(struct timeval start, struct timeval end)
{
  struct timeval randomTime;
  randomTime.tv_usec = 0;

  time_t R = esp_random();
  time_t i = start.tv_sec;
  time_t j = end.tv_sec;

  randomTime.tv_sec = (R % (j - i)) + i;
  return randomTime;
}

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
 *
 *
 * |-----------|-----------|.....|-----------|
 * 0    ^     i_1    ^    i_2   i_n-1   ^    183
 *      |            |                  |
 *      |            |                  |
 * one random event -|           one random event
*/
void segmentation(struct timeval *events,
                  struct timeval start,
                  struct timeval end)
{
  // int numSegments = (int) floor(EXP_TIME_SECONDS / NUM_EVENTS);
  return;
}

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