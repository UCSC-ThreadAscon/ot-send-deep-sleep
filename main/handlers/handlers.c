#include "main.h"

void onPowerOn(nvs_handle_t handle,
               struct timeval *events,
               uuid *deviceId,
               Data *dataPtr)
{
  initEventsArray(events);
  nvsWriteBlob(handle, NVS_EVENTS_ARRAY, events, EVENTS_ARRAY_SIZE);

  generateUUID(deviceId);
  nvsWriteBlob(handle, NVS_UUID, deviceId, UUID_SIZE_BYTES);

  uint8_t eventsIndex = 0;
  nvsWriteByteUInt(handle, NVS_EVENTS_INDEX, eventsIndex);

  dataPtr->batterySleepMicro = BATTERY_WAIT_TIME_MICRO;
  dataPtr->status = PowerOn;
  nvsWriteBlob(handle, NVS_DATA, dataPtr, sizeof(Data));

  printDeviceInfo();

#if NVS_DEBUG
  printEventsArray(events, NUM_EVENTS);
#endif

  return;
}

void sendEventPacket(otSockAddr *socket, uuid deviceId)
{
  *socket = createSocket(CONFIG_SERVER_IP_ADDRESS);
  EventPayload event = createEventPayload(deviceId);
  request(socket, (void *) &event, sizeof(event), EVENT_URI);
  return;
}

void sendBatteryPacket(otSockAddr *socket, uuid deviceId)
{
  *socket = createSocket(CONFIG_SERVER_IP_ADDRESS);
  BatteryPayload battery = createBatteryPayload(deviceId);
  request(socket, (void *) &battery, sizeof(battery), BATTERY_URI);
  return;
}