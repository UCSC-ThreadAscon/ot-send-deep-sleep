#include "main.h"

void onPowerOn(nvs_handle_t handle, struct timeval *events,
               uuid *deviceId, struct timeval *batteryWakeup,
               struct timeval tvNow)
{
  initEventsArray(events, tvNow, getFutureTimeval(EXP_TIME_SECONDS_TEST));
  nvsWriteBlob(handle, NVS_EVENTS_ARRAY, events, EVENTS_ARRAY_SIZE);

  generateUUID(deviceId);
  nvsWriteBlob(handle, NVS_UUID, deviceId, UUID_SIZE_BYTES);

  uint8_t eventsIndex = 0;
  nvsWriteByteUInt(handle, NVS_EVENTS_INDEX, eventsIndex);

  PacketSendType packetType = BatteryPacket;
  nvsWriteByteUInt(handle, NVS_PACKET_TYPE, packetType);

  moveToNextBatteryWakeup(handle, batteryWakeup, tvNow);

#if NVS_DEBUG
  printEventsArray(events, NUM_EVENTS);
#endif
#if SHOW_DEBUG_STATS
  DebugStats stats = initDebugStats(tvNow);
  writeDebugStats(&stats, handle);
#endif

  return;
}

void sendEventPacket(otSockAddr *socket, uuid deviceId,
                     nvs_handle_t handle)
{
  *socket = createSocket(CONFIG_SERVER_IP_ADDRESS);
  EventPayload event = createEventPayload(deviceId);
  request(socket, (void *) &event, sizeof(event));

#if SHOW_DEBUG_STATS
  DebugStats stats = readDebugStats(handle);
  stats.eventPacketsSent += 1;
  writeDebugStats(&stats, handle);
  printDebugStats(stats, handle);
#endif

  return;
}

void sendBatteryPacket(otSockAddr *socket, uuid deviceId,
                       nvs_handle_t handle)
{
#if SHOW_DEBUG_STATS
  DebugStats stats = readDebugStats(handle);
  stats.batteryPacketsSent += 1;
  writeDebugStats(&stats, handle);
  printDebugStats(stats, handle);
#endif

  deepSleepStart();
  return;
}