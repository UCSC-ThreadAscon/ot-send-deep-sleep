#pragma once

#include "utilities.h"
#include "workload.h"
#include "init.h"
#include "time.h"
#include "sleep.h"
#include "storage.h"

#define NVS_NAMESPACE "sed_nvs"

#define NUM_EVENTS NUM_EVENTS_AIR_MONITOR
#define NVS_EVENTS_ARRAY "events"

#define JUST_POWERED_ON !isDeepSleepWakeup()

void onPowerOn(struct timeval *events);
void onDeepSleepWakeup(struct timeval *events);

void initEventsArray(struct timeval *events,
                     struct timeval start,
                     struct timeval end);