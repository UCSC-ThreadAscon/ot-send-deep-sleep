#include "main.h"

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

static inline void moveOnToNextEvent(nvs_handle_t handle,
                                     uint8_t currentEventsIndex)
{
  currentEventsIndex += 1;
  nvsWriteByteUInt(handle, NVS_EVENTS_INDEX, currentEventsIndex);
  return;
}

static inline bool noMoreEventsToSend(uint8_t eventsIndex)
{
  return eventsIndex >= NUM_EVENTS ? true : false;
}

void onWakeup(nvs_handle_t handle,
              struct timeval *events,
              uuid *deviceId,
              otSockAddr *socket)
{
  uint8_t eventsIndex = nvsReadByteUInt(handle, NVS_EVENTS_INDEX);

  if (!noMoreEventsToSend(eventsIndex))
  {
    struct timeval tvNow = getCurrentTimeval();
    struct timeval tvCurrentEvent = events[eventsIndex];
    uint64_t nextEventSleepTime = timeDiffMs(tvNow, tvCurrentEvent);

    initDeepSleepTimerMs(nextEventSleepTime);
    moveOnToNextEvent(handle, eventsIndex);

    if (isDeepSleepWakeup())
    {
      coapStart();
      sendEventPacket(socket, *deviceId);
    }
    else 
    {
      deepSleepStart();
    }
  }

#if NVS_DEBUG
  if (!noMoreEventsToSend(eventsIndex))
  {
    otLogNotePlat("Sent %" PRIu8 " Event Packets so far.", eventsIndex - 1);
  }
  else
  {
    otLogNotePlat("Sent all Event Packets.");
  }
  printEventsIndex(eventsIndex);
#endif

  return;
}