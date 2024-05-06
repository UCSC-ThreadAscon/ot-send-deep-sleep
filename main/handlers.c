#include "main.h"

void onPowerOn(struct timeval *events,
               uuid *deviceId,
               EventsIndex *indexPtr)
{
  nvs_handle_t handle;
  openReadWrite(NVS_NAMESPACE, &handle);

  initEventsArray(events, getCurrentTimeval(),
                  getFutureTimeval(EXP_TIME_SECONDS_TEST));
  nvsWriteArray(handle, NVS_EVENTS_ARRAY, events, EVENTS_ARRAY_SIZE);

  generateUUID(deviceId);
  nvsWriteArray(handle, NVS_UUID, deviceId, UUID_SIZE_BYTES);

  *indexPtr = initEventsIndex(handle);

#if NVS_DEBUG
  printEventsArray(events, NUM_EVENTS);
  printUUID(deviceId);
  printEventsIndex(*indexPtr);
#endif

  nvs_close(handle);
  return;
}

void sendEventPacket(otSockAddr *socket, uuid deviceId)
{
  *socket = createSocket(CONFIG_SERVER_IP_ADDRESS);
  EventPayload event = createEventPayload(deviceId);
  request(socket, (void *) &event, sizeof(event));
  return;
}