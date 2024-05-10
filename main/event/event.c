#include "main.h"
#include "math.h"

/**
 * STEP 3: AVOID OVERLAP WITH BATTERY
 * ----------------------------------
 * Battery packets are sent EVERY 30 SECONDS, and the FIRST battery packet
 * is sent WHEN POWERED ON. As a result, add 15 seconds to each event wakeup time
 * so minimize overlap between when two battery packets are sent.
 *
 *   B-----------------X----------------B
 *   ^                 ^                ^
 *   |                 |                |
 *   |                 |                |
 *  Battery           Send          Another one
 *  packet            event         Sent 30 seconds
 *  sent            packet here!    later
*/
void avoidBatteryOverlap(struct timeval *events)
{
  for (int e = 0; e < NUM_EVENTS; e++)
  {
    struct timeval event = events[e];
    event.tv_sec += 15;
    events[e] = event;
  }
  return;
}

/*
 * STEP 2: Use Seconds
 * -------------------
 *  Choose a random time in [i, j), where i and j are EXACT SECONDS
 *  (not ms or us, SECONDS). The random time R will also be in EXACT SECONDS.
 *
 *  |-----------|
 *  i     ^     j
 *        |
 *        |
 *        R
 *
 * where R = r (mod (j - i)) + i,
 * and   r = esp_random();
 */
struct timeval randomSeconds(time_t iMins, time_t jMins)
{
  struct timeval randomTime;
  EmptyMemory(&randomTime, sizeof(struct timeval));

  time_t R = esp_random();
  time_t randomMins = (R % (jMins - iMins)) + iMins;

  randomTime.tv_sec = MINUTES_TO_SECONDS(randomMins);
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
 * In addition, segementation also AVOIDS OVERLAP BETWEEN CONSECUTIVE EVENTS,
 * only one event will appear in each segment.
 *
 * |-----------|-----------|.....|-----------|
 * 0    ^     a_1    ^    a_2   a_n-1   ^    183
 *      |            |                  |
 *      |            |                  |
 * one random event -|           one random event
*/
void segmentation(struct timeval *events,
                  struct timeval start,
                  struct timeval end)
{
  time_t segmentDurMins = (time_t) floor(EXP_TIME_MINUTES / NUM_EVENTS);

  time_t iMins = (time_t) floor(SECONDS_TO_MINUTES((double) start.tv_sec));

  for (int e = 0; e < NUM_EVENTS; e++) {
    time_t jMins = iMins + segmentDurMins;
    events[e] = randomSeconds(iMins, jMins);

    // Equivalent to "i.Mins += segmentDurMins".
    iMins = jMins;
  }

  return;
}

void initEventsArray(struct timeval *events)
{
  struct timeval now = getTimevalNow();
  struct timeval expEnd = getFutureTimeval(EXP_TIME_SECONDS);

  segmentation(events, now, expEnd);
  avoidBatteryOverlap(events);
  return;
}