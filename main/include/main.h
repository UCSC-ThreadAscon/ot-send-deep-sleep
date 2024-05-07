#pragma once

#include "utilities.h"
#include "workload.h"
#include "time.h"
#include "sleep.h"

#include "init.h"
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
void onWakeup(nvs_handle_t handle, struct timeval *events, uuid *deviceId);
void wakeupInit(nvs_handle_t handle, struct timeval *events, uuid *deviceId);

void initEventsArray(struct timeval *events,
                     struct timeval start,
                     struct timeval end);
void sendEventPacket(otSockAddr *socket, uuid deviceId);

void printEventsIndex(uint8_t index);
