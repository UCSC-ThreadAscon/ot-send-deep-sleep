/**
 * BATTERY BACKOFF STRATEGY
 * ------------------------
 * This file defines the functions used to ensure that every batter and
 * event packet are always sent no more than 1 second apart.
 *
 * This invariant will prevent the case in which a battery and event packet
 * are sent so close together, that by the time the device wakes up from
 * deep sleep, the event has already been passed and no event ever gets sent again.
*/
#include "main.h"

#define MARGIN_SECONDS 1
#define BACKOFF_SECONDS 2
#define MARGIN_US SECONDS_TO_US(MARGIN_SECONDS)
#define BACKOFF_US SECONDS_TO_US(BACKOFF_SECONDS)

uint64_t batteryBackoff(uint64_t eventsSleepUs,
                        uint64_t batterySleepUs)
{
  /**
   * CASE: Battery Packet Sent First
   *       (or Battery and Event Packets sent at the same time)
   *
   * Before:                After:
   * |---B-----E----|       |--------E---------B-|  
   *     |-----|                     |---------|
   *        ^                             ^
   *        |                             |
   *        |                             |
   *      <= 1 second                   2 seconds difference
   *
   * In this case move the battery packet to 2 SECONDS AFTER
   * the event packet.
   *
   * This approach will even deal with the case when both packets are
   * originally going to be sent AT THE SAME TIME!
   *
   * Before:                After:
   *        B
   * |------E-------|       |------E----------B-|
   *        ^                      |----------|
   *        |                           ^
   *        |                           |
   *        |                           |
   *     same time               2 second difference        
  */
  if (batterySleepUs <= eventsSleepUs)
  {
    uint64_t diffUs = eventsSleepUs - batterySleepUs;
    if (diffUs <= MARGIN_US)
    {
      return batterySleepUs + diffUs + BACKOFF_US;
    }
  }

  /**
   * CASE: Event Packet Sent First
   *
   * Add 2 seconds more to the when the battery packet should be sent.
   *
   * Not as much of a concern, but do the backoff anyways as a precaution.
   *
   * Before:                  After:
   * |---E-----B----|         |---E----------B----|
   *     |-----|                  |----------|
   *        ^                          ^
   *        |                          |
   *        |                          |
   *      <= 1 second               2 seconds more
  */
  else {
    uint64_t diffUs = batterySleepUs - eventsSleepUs;
    if (diffUs <= MARGIN_US)
    {
      return batterySleepUs + BACKOFF_US;
    }
  }

  return batterySleepUs;
}
