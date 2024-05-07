#pragma once
#include <stdbool.h>

/**
 * Battery lifetime packets will be sent every 30 SECONDS.
*/
#define BATTERY_WAIT_TIME_MS 1000 * 30

/*
 * The duration of each experimential trial will always be:
 *
 *    30 seconds * 365 days = 10950 seconds ~= 182.5 minutes
 *
 * The ceil(182.5) = 183 minutes, and 183 minutes is equivalent to
 * exactly 10980 seconds.
*/
#define EXP_TIME_SECONDS 10980

#define NUM_EVENTS_FRONT_DOOR 36
#define NUM_EVENTS_AIR_MONITOR 10
#define NUM_EVENTS_SECOND_STORY 1
