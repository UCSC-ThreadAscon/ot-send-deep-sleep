#include "main.h"

void onPowerOn(nvs_handle_t handle, struct timeval *events, uuid *deviceId)
{
  initEventsArray(events, getCurrentTimeval(),
                  getFutureTimeval(EXP_TIME_SECONDS_TEST));
  nvsWriteArray(handle, NVS_EVENTS_ARRAY, events, EVENTS_ARRAY_SIZE);

  generateUUID(deviceId);
  nvsWriteArray(handle, NVS_UUID, deviceId, UUID_SIZE_BYTES);

  uint8_t eventsIndex = 0;
  nvsWriteByteUInt(handle, NVS_EVENTS_INDEX, eventsIndex);

#if NVS_DEBUG
  printEventsArray(events, NUM_EVENTS);
  printUUID(deviceId);
  printEventsIndex(eventsIndex);
#endif

  return;
}

void sendEventPacket(otSockAddr *socket, uuid deviceId)
{
  *socket = createSocket(CONFIG_SERVER_IP_ADDRESS);
  EventPayload event = createEventPayload(deviceId);
  request(socket, (void *) &event, sizeof(event));
  return;
}