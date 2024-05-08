#pragma once

#include "utilities.h"
#include "workload.h"
#include "time_api.h"
#include "sleep.h"

#include "experiment.h"
#include "init.h"
#include "event.h"
#include "battery.h"
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
#define NVS_PACKET_TYPE "packet_type"
#define NVS_BATTERY_WAKEUP "battery_wakeup"
#define NVS_DEBUG_STATS "debug_stats"

typedef enum PacketSendType
{
  EventPacket,
  BatteryPacket
}
PacketSendType;

void onPowerOn(nvs_handle_t handle, struct timeval *events,
               uuid *deviceId, struct timeval *batteryWakeup,
               struct timeval tvNow);
void wakeupInit(nvs_handle_t handle, struct timeval *events, uuid *deviceId,
                struct timeval *batteryWakeup);

void onWakeup(nvs_handle_t handle,
              struct timeval *events,
              uuid *deviceId,
              otSockAddr *socket,
              struct timeval *batteryWakeup,
              struct timeval tvNow);

typedef struct DebugStats
{
  int eventPacketsSent;
  int batteryPacketsSent;
  struct timeval powerOnTime;
}
DebugStats;

DebugStats initDebugStats(struct timeval tvNow);
void printDebugStats(DebugStats stats, nvs_handle_t handle);
bool noMoreEventsToSend(uint8_t eventsIndex);
void printPacketType(PacketSendType packetType);
