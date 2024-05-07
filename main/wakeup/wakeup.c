#include "main.h"

void wakeupInit(nvs_handle_t handle,
                struct timeval *events,
                uuid *deviceId)
{
  nvsReadArray(handle, NVS_EVENTS_ARRAY, events, EVENTS_ARRAY_SIZE);
  nvsReadArray(handle, NVS_UUID, deviceId, UUID_SIZE_BYTES);

#if NVS_DEBUG
  printEventsArray(events, NUM_EVENTS);
  printUUID(deviceId);
#endif

  return;
}

void onWakeup(struct timeval *events, uuid *deviceId)
{
  nvs_handle_t handle;
  openReadWrite(NVS_NAMESPACE, &handle);
  wakeupInit(handle, events, deviceId);

  uint8_t eventsIndex = nvsReadByteUInt(handle, NVS_EVENTS_INDEX);
  if (eventsIndex < NUM_EVENTS)
  {
    eventsIndex += 1;
    nvsWriteByteUInt(handle, NVS_EVENTS_INDEX, eventsIndex);
  }

#if NVS_DEBUG
  printEventsIndex(eventsIndex);
#endif

  nvs_close(handle);
  return;
}