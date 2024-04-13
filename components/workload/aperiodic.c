/**
 * The function that determine the rate at which aperiodic packets are
 * sent is from the paper by Betzler et al.:
 * https://www.mdpi.com/1424-8220/14/8/14932
 *
 * Additional resources used:
 * https://en.wikibooks.org/wiki/C_Programming/math.h/log
 * https://en.wikibooks.org/wiki/C_Programming/limits.h
*/
#include "workload.h"

/**
 * For the device near the washing machine, there is a 3% chance
 * that a water leakage will occur.
*/
bool waterLeakOccured() {
  uint32_t random = esp_random() % 100;
  if (random < 3) {
    otLogNotePlat("A water leakage has occured!");
    return true;
  }
  return false;
}

/**
 * For the device upstairs, there is a 1% chance that someone
 * will visit the second story door.
*/
bool someoneAtSecondStory() {
  uint32_t random = esp_random() % 100;
  if (random < 1) {
    otLogNotePlat("Someone detected at the second story door!");
    return true;
  }
  return false;
}

/**
 * For the device at the front door, there is a 29% chance that someone
 * will visit the front door.
*/
bool someoneAtFrontDoor() {
  uint32_t random = esp_random() % 100;
  if (random < 29) {
    otLogNotePlat("Someone detected at the front door!");
    return true;
  }
  return false;
}