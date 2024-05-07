#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <stdbool.h>

#define POLL_PERIOD_MS CONFIG_POLL_PERIOD

#define BORDER_ROUTER_URI "resource"

#define BATTERY_WAIT_TIME_MS 1000 * 30 // 30 seconds

#define EXP_TIME_SECONDS 10980 // ~183 minutes

#define NUM_EVENTS_FRONT_DOOR 36
#define NUM_EVENTS_AIR_MONITOR 10
#define NUM_EVENTS_SECOND_STORY 1

#endif // EXPERIMENT_H