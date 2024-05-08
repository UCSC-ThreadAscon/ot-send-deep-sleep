#pragma once

#include "utilities.h"
#include "workload.h"
#include "time_api.h"
#include "sleep.h"

#include "experiment.h"
#include "init.h"
#include "event.h"
#include "payload.h"
#include "storage.h"
#include "uuid.h"
#include "flags.h"

#define JUST_POWERED_ON !isDeepSleepWakeup()

#define EVENTS_ARRAY_SIZE NUM_EVENTS * sizeof(struct timeval)

#define NVS_NAMESPACE "sed_nvs"
#define NVS_EVENTS_ARRAY "events"
#define NVS_UUID "uuid"
#define NVS_EVENTS_INDEX "events_index"
#define NVS_DATA "status"

typedef enum Status {
  PowerOn,
  Event,
  Battery
} Status;

typedef struct Data {
  uint64_t batterySleepTime; // in milliseconds
  Status status;
} Data;

void onPowerOn(nvs_handle_t handle,
               struct timeval *events,
               uuid *deviceId,
               Data *dataPtr);

void wakeupInit(nvs_handle_t handle,
                struct timeval *events,
                uuid *deviceId,
                Data *dataPtr);

void onWakeup(nvs_handle_t handle,
              struct timeval *events,
              uuid *deviceId,
              otSockAddr *socket,
              Data *data);

void sendBatteryPacket(otSockAddr *socket, uuid deviceId);
void sendEventPacket(otSockAddr *socket, uuid deviceId);

bool noMoreEventsToSend(uint8_t eventsIndex);
void eventPacketsStats(uint8_t eventsIndex);
