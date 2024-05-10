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

uint64_t batteryBackoff(uint64_t eventsSleepMicro,
                        uint64_t batterySleepMicro)
{
  bool sendBatteryNext = batterySleepMicro <= eventsSleepMicro;

  /**
   * CASE: Battery Packet Sent First
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
  if (sendBatteryNext)
  {

  }

  return 0;
}
