#pragma once

#include "utilities.h"
#include "workload.h"
#include "init.h"
#include "time.h"
#include "sleep.h"
#include "storage.h"
#include "uuid.h"

#define DEBUG 1

#define NVS_NAMESPACE "sed_nvs"

#define NUM_EVENTS NUM_EVENTS_AIR_MONITOR
#define EVENTS_ARRAY_SIZE NUM_EVENTS * sizeof(struct timeval)
#define NVS_EVENTS_ARRAY "events"

#define NVS_UUID "uuid"

#define JUST_POWERED_ON !isDeepSleepWakeup()

void onPowerOn(struct timeval *events, uuid *deviceId);
void onDeepSleepWakeup(struct timeval *events);

void initEventsArray(struct timeval *events,
                     struct timeval start,
                     struct timeval end);