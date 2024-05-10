/**
 * BATTERY BACKOFF STRATEGY
 * ------------------------
 * This file defines the functions used to ensure that every batter and
 * event packet are always sent no more than 1 second apart.
 *
 * This invariatn will prevent events in which the batter and event packet
 * are sent so close together, than by the time the device wakes up from
 * deep sleep, the event has already been passed and no event ever gets sent again.
*/
#include "main.h"
