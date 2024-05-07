#pragma once

#include "utilities.h"
#include "workload.h"
#include "time_api.h"
#include "sleep.h"

#include "init.h"
#include "event.h"
#include "payload.h"
#include "storage.h"
#include "uuid.h"
#include "flags.h"

#define JUST_POWERED_ON !isDeepSleepWakeup()

#define NUM_EVENTS NUM_EVENTS_AIR_MONITOR
#define EVENTS_ARRAY_SIZE NUM_EVENTS * sizeof(struct timeval)

#define NVS_NAMESPACE "sed_nvs"
#define NVS_EVENTS_ARRAY "events"
#define NVS_UUID "uuid"
#define NVS_EVENTS_INDEX "events_index"

void onPowerOn(nvs_handle_t handle, struct timeval *events, uuid *deviceId);
void wakeupInit(nvs_handle_t handle, struct timeval *events, uuid *deviceId);

void onWakeup(nvs_handle_t handle,
              struct timeval *events,
              uuid *deviceId,
              otSockAddr *socket);

bool noMoreEventsToSend(uint8_t eventsIndex);
void eventPacketsStats(uint8_t eventsIndex);
