#include "main.h"
#include "assert.h"

void wakeupInit(nvs_handle_t handle, struct timeval *events, uuid *deviceId)
{
  nvsReadArray(handle, NVS_EVENTS_ARRAY, events, EVENTS_ARRAY_SIZE);
  nvsReadArray(handle, NVS_UUID, deviceId, UUID_SIZE_BYTES);

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
    uint64_t sleepTime = getNextSleepTime(events, eventsIndex);
    initDeepSleepTimerMs(sleepTime);
    incrementEventsIndex(handle, eventsIndex);
  }

  if (isDeepSleepWakeup())
  {
    coapStart();
    sendEventPacket(socket, *deviceId);
  }
  else
  {
    deepSleepStart();
  }

#if SHOW_DEBUG_STATS
  eventPacketsStats(eventsIndex);
#endif

  return;
}