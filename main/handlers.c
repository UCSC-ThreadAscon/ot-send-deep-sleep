#include "main.h"

void onPowerOn(struct timeval *events, uuid *deviceId)
{
  nvs_handle_t handle;
  openReadWrite(NVS_NAMESPACE, &handle);

  initEventsArray(events, getCurrentTimeval(), getFutureTimeval(EXP_TIME_SECONDS));
  nvsWriteArray(&handle, NVS_EVENTS_ARRAY, events, EVENTS_ARRAY_SIZE);

  generateUUID(deviceId);
  nvsWriteArray(&handle, NVS_UUID, deviceId, UUID_SIZE_BYTES);

#if NVS_DEBUG
  printEventsArray(events, NUM_EVENTS);
  printUUID(deviceId);
#endif

  nvs_close(handle);
  return;
}

void onDeepSleepWakeup(struct timeval *events, uuid *deviceId)
{
  nvs_handle_t handle;
  openReadWrite(NVS_NAMESPACE, &handle);

  nvsReadArray(&handle, NVS_EVENTS_ARRAY, events, EVENTS_ARRAY_SIZE);
  nvsReadArray(&handle, NVS_UUID, deviceId, UUID_SIZE_BYTES);

#if NVS_DEBUG
  printEventsArray(events, NUM_EVENTS);
  printUUID(deviceId);
#endif

  nvs_close(handle);
  return;
}