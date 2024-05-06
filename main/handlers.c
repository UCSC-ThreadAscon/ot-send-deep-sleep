#include "main.h"

void onPowerOn(struct timeval *events, uuid *deviceId)
{
  nvs_handle_t handle;
  openReadWrite(NVS_NAMESPACE, &handle);

  initEventsArray(events, getCurrentTimeval(), getFutureTimeval(EXP_TIME_SECONDS));
  nvsWriteArray(&handle, NVS_EVENTS_ARRAY, events, EVENTS_ARRAY_SIZE);

  generateUUID(deviceId);
  nvsWriteArray(&handle, NVS_UUID, deviceId, UUID_SIZE_BYTES);

#if DEBUG
  printEventsArray(events, NUM_EVENTS);

  uint8_t buffer[UUID_SIZE_BYTES];
  EmptyMemory(&buffer, UUID_SIZE_BYTES);
  memcpy(&buffer, &(deviceId->bytes), UUID_SIZE_BYTES);
  hexDump(&buffer, UUID_SIZE_BYTES, "Device ID");
#endif

  nvs_close(handle);
  return;
}

void onDeepSleepWakeup(struct timeval *events)
{
  nvs_handle_t handle;
  openReadWrite(NVS_NAMESPACE, &handle);

  nvsReadArray(&handle, NVS_EVENTS_ARRAY, events, EVENTS_ARRAY_SIZE);
  printEventsArray(events, NUM_EVENTS);

  nvs_close(handle);
  return;
}