#include "main.h"

void wakeupInit(struct timeval *events,
                uuid *deviceId,
                EventsIndex *indexPtr)
{
  nvs_handle_t handle;
  openReadWrite(NVS_NAMESPACE, &handle);

  nvsReadArray(handle, NVS_EVENTS_ARRAY, events, EVENTS_ARRAY_SIZE);
  nvsReadArray(handle, NVS_UUID, deviceId, UUID_SIZE_BYTES);
  *indexPtr = readEventsIndex(handle);

#if NVS_DEBUG
  printEventsArray(events, NUM_EVENTS);
  printUUID(deviceId);
  printEventsIndex(*indexPtr);
#endif

  nvs_close(handle);
  return;
}

void onWakeup(struct timeval *events, uuid *deviceId, EventsIndex *indexPtr)
{
  wakeupInit(events, deviceId, indexPtr);
  return;
}