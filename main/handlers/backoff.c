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

#define MARGIN_SECONDS 5
#define BACKOFF_SECONDS 5
#define MARGIN_US SECONDS_TO_US(MARGIN_SECONDS)
#define BACKOFF_US SECONDS_TO_US(BACKOFF_SECONDS)

void batteryBackoffDebug(uint64_t diffUs, bool batteryFirst) {
  double diffSecs = US_TO_SECONDS((double) diffUs);

  if (batteryFirst) {
    otLogWarnPlat("Battery will be sent ~%.3f secs before Event.", diffSecs);
  }
  else {
    otLogWarnPlat("Event will be sent ~%.3f secs before Battery.", diffSecs);
  }

  otLogWarnPlat("Going to do battery backoff by %d secs.", BACKOFF_SECONDS);
  return;
}

uint64_t batteryBackoff(uint64_t eventSleepUs,
                        uint64_t batterySleepUs)
{
#if TIME_DIFF_DEBUG
    printSleepTimes(eventSleepUs, batterySleepUs);
#endif

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
   * <= MARGIN_SECONDS second    BACKOFF_SECONDS seconds difference
   *
   * In this case move the battery packet to BACKOFF_SECONDS AFTER
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
   *     same time         BACKOFF_SECONDS second difference        
  */
  if (batterySleepUs <= eventSleepUs)
  {
    uint64_t diffUs = eventSleepUs - batterySleepUs;
    if (diffUs <= MARGIN_US)
    {
#if TIME_DIFF_DEBUG
      batteryBackoffDebug(diffUs, true);
#endif
      return batterySleepUs + diffUs + BACKOFF_US;
    }
  }

  /**
   * CASE: Event Packet Sent First
   *
   * Add BACKOFF_SECONDS more to the when the battery packet should be sent.
   *
   * Not as much of a concern, but do the backoff anyways as a precaution.
   *
   * Before:                  After:
   * |---E-----B----|         |---E----------B----|
   *     |-----|                  |----------|
   *        ^                          ^
   *        |                          |
   *        |                          |
   *  <= MAGIN_SECONDS second     +BACKOFF_SECONDS seconds more
  */
  else {
    uint64_t diffUs = batterySleepUs - eventSleepUs;
    if (diffUs <= MARGIN_US)
    {
#if TIME_DIFF_DEBUG
      batteryBackoffDebug(diffUs, false);
#endif
      return batterySleepUs + BACKOFF_US;
    }
  }

  return batterySleepUs;
}
