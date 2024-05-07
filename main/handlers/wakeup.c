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

uint64_t getNextBatterySleepTime(struct timeval batteryWakeupTime,
                                 struct timeval tvNow)
{
  return timeDiffMs(tvNow, batteryWakeupTime);
}

void setPacketType(nvs_handle_t handle, PacketSendType packetType)
{
  nvsWriteByteUInt(handle, NVS_PACKET_TYPE, packetType);
  return;
}

void setEventSleepTime(nvs_handle_t handle,
                       uint64_t sleepTime,
                       uint8_t eventsIndex)
{
  setPacketType(handle, EventPacket);
  initDeepSleepTimerMs(sleepTime);
  incrementEventsIndex(handle, eventsIndex);
  return;
}

void setBatterySleepTime(nvs_handle_t handle,
                         uint64_t sleepTime,
                         struct timeval *batteryWakeup,
                         struct timeval tvNow)
{
  setPacketType(handle, BatteryPacket);
  initDeepSleepTimerMs(sleepTime);
  moveToNextBatteryWakeup(handle, batteryWakeup, tvNow);
  return;
}

void onWakeup(nvs_handle_t handle,
              struct timeval *events,
              uuid *deviceId,
              otSockAddr *socket,
              struct timeval *batteryWakeup,
              struct timeval tvNow)
{
  uint8_t eventsIndex = nvsReadByteUInt(handle, NVS_EVENTS_INDEX);
  PacketSendType packetType = nvsReadByteUInt(handle, NVS_PACKET_TYPE);

  coapStart();
  if (packetType == EventPacket)
  {
    sendEventPacket(socket, *deviceId);
  }
  else
  {
    sendBatteryPacket(socket, *deviceId);
  }

  uint64_t nextBatterySleepTime = getNextBatterySleepTime(*batteryWakeup, tvNow);
  otLogNotePlat("The next battery sleep time is %" PRIu64 ".", nextBatterySleepTime);

  if (!noMoreEventsToSend(eventsIndex))
  {
    uint64_t nextEventSleepTime = getNextEventSleepTime(events, eventsIndex, tvNow);
    if (nextEventSleepTime <= nextBatterySleepTime)
    {
      setEventSleepTime(handle, nextEventSleepTime, eventsIndex);
    }
    else
    {
      setBatterySleepTime(handle, nextBatterySleepTime, batteryWakeup, tvNow);
    }
  }
  else
  {
    setBatterySleepTime(handle, nextBatterySleepTime, batteryWakeup, tvNow);
  }

#if SHOW_DEBUG_STATS
  eventPacketsStats(eventsIndex);
  printPacketType(packetType);
#endif

  return;
}