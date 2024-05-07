#include "main.h"
#include "assert.h"

void wakeupInit(nvs_handle_t handle, struct timeval *events, uuid *deviceId,
                struct timeval *nextBatteryWakeup)
{
  nvsReadBlob(handle, NVS_EVENTS_ARRAY, events, EVENTS_ARRAY_SIZE);
  nvsReadBlob(handle, NVS_UUID, deviceId, UUID_SIZE_BYTES);
  nvsReadBlob(handle, NVS_BATTERY_WAKEUP, nextBatteryWakeup, sizeof(struct timeval));

#if NVS_DEBUG
  printEventsArray(events, NUM_EVENTS);
  printUUID(deviceId);
  printBatteryWakeup(*nextBatteryWakeup);
#endif

  return;
}

static inline void incrementEventsIndex(nvs_handle_t handle,
                                        uint8_t currentEventsIndex)
{
  currentEventsIndex += 1;
  nvsWriteByteUInt(handle, NVS_EVENTS_INDEX, currentEventsIndex);
  return;
}

uint64_t getNextEventSleepTime(struct timeval *events, uint8_t eventsIndex,
                               struct timeval tvNow)
{
    struct timeval tvNextEvent = events[eventsIndex];
    return timeDiffMs(tvNow, tvNextEvent);
}

uint64_t getNextBatterySleepTime(struct timeval nextBatteryWakeupTime,
                                 struct timeval tvNow)
{
  return timeDiffMs(tvNow, nextBatteryWakeupTime);
}

void setPacketType(nvs_handle_t handle, PacketSendType packetType)
{
  nvsWriteByteUInt(handle, NVS_PACKET_TYPE, packetType);
  return;
}

void onWakeup(nvs_handle_t handle,
              struct timeval *events,
              uuid *deviceId,
              otSockAddr *socket)
{
  uint8_t eventsIndex = nvsReadByteUInt(handle, NVS_EVENTS_INDEX);
  PacketSendType packetType = nvsReadByteUInt(handle, NVS_PACKET_TYPE);

  if (packetType == EventPacket)
  {
    coapStart();
    sendEventPacket(socket, *deviceId);
  }

  /**
   * ---- TO-DO ----
   * 1. Determine the next event wakeup time.
   * 2. Compare that to the next battery wakeup time.
   * 3. Determine which is less. You will send that one next.
   *    Then sleep for the lesser amount of time.
  */
  if (!noMoreEventsToSend(eventsIndex))
  {
    struct timeval tvNow = getCurrentTimeval();
    uint64_t nextEventSleepTime = getNextEventSleepTime(events, eventsIndex, tvNow);

    initDeepSleepTimerMs(nextEventSleepTime);
    incrementEventsIndex(handle, eventsIndex);

    setPacketType(handle, EventPacket);
  }
  else
  {
    setPacketType(handle, BatteryPacket);
  }

  if (JUST_POWERED_ON)
  {
    sendBatteryPacket(socket, *deviceId);
  }

#if SHOW_DEBUG_STATS
  eventPacketsStats(eventsIndex);
  printPacketType(packetType);
#endif

  return;
}