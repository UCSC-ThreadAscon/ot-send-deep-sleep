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

void onWakeup(nvs_handle_t handle, struct timeval *events, uuid *deviceId)
{
  uint8_t eventsIndex = nvsReadByteUInt(handle, NVS_EVENTS_INDEX);

  /** TO-DO: Figure out how long to sleep for. */
  initDeepSleepTimerMs(BATTERY_WAIT_TIME_MS_TEST);

  if (isDeepSleepWakeup() && (eventsIndex < NUM_EVENTS))
  {
    eventsIndex += 1;
    nvsWriteByteUInt(handle, NVS_EVENTS_INDEX, eventsIndex);
  }

#if NVS_DEBUG
  printEventsIndex(eventsIndex);
#endif
  return;
}