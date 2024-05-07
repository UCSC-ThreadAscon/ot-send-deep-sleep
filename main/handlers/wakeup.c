#include "main.h"
#include "assert.h"

void wakeupInit(nvs_handle_t handle, struct timeval *events, uuid *deviceId)
{
  nvsReadBlob(handle, NVS_EVENTS_ARRAY, events, EVENTS_ARRAY_SIZE);
  nvsReadBlob(handle, NVS_UUID, deviceId, UUID_SIZE_BYTES);

#if NVS_DEBUG
  printEventsArray(events, NUM_EVENTS);
  printUUID(deviceId);
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

uint64_t getNextSleepTime(struct timeval *events, uint8_t eventsIndex)
{
    struct timeval tvNow = getCurrentTimeval();
    struct timeval tvNextEvent = events[eventsIndex];
    return timeDiffMs(tvNow, tvNextEvent);
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
    uint64_t sleepTime = getNextSleepTime(events, eventsIndex);
    initDeepSleepTimerMs(sleepTime);
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