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

void onWakeup(nvs_handle_t handle,
              struct timeval *events,
              uuid *deviceId,
              otSockAddr *socket)
{
  uint8_t eventsIndex = nvsReadByteUInt(handle, NVS_EVENTS_INDEX);

  if (!noMoreEventsToSend(eventsIndex))
  {
    /**
     * TO-DO:
     *  1. Get sleep time for event packet.
     *  2. Get sleep time for battery packet.
     *
     *  3(a). If event packet is less, then you will send event packet
     *        on next wakeup.
     *
     *        battery sleep time in NVS = battery sleep time - event packet sleep time.
     *
     *  3(b). If battery packet is less, you will send a battery packet on next
     *        wakeup.
     *
     *        battery sleep time in NVS = 30 seconds.
     *
     * 4. Whatever you decided on the previous wakeup, send that type of packet.
    */
    uint64_t eventSleepTime = getNextSleepTime(events, eventsIndex);
    initDeepSleepTimerMs(eventSleepTime);
    incrementEventsIndex(handle, eventsIndex);
  }

  coapStart();
  if (isDeepSleepWakeup()) {
    sendEventPacket(socket, *deviceId);
  }
  else {
    // The device has just been powered on.
    // The first packet to send will ALWAYS be the battery packet.
    sendBatteryPacket(socket, *deviceId);
  }

#if EVENT_DEBUG
  eventPacketsStats(eventsIndex);
#endif

  return;
}