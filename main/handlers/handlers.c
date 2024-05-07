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
  // printUUID(deviceId);
  // printEventsIndex(eventsIndex);
  // printPacketType(packetType);
  // printBatteryWakeup(*batteryWakeup);
#endif

  return;
}

static int eventPacketsSent = 0;
static int batteryPacketsSent = 0;

void printStats() {
  otLogNotePlat("Sent %d event packets so far.", eventPacketsSent);
  otLogNotePlat("Sent %d battery packets so far.", batteryPacketsSent);
}

void sendEventPacket(otSockAddr *socket, uuid deviceId)
{
  *socket = createSocket(CONFIG_SERVER_IP_ADDRESS);
  EventPayload event = createEventPayload(deviceId);
  request(socket, (void *) &event, sizeof(event));

#if SHOW_DEBUG_STATS
  eventPacketsSent += 1;
  printStats();
#endif
  return;
}

void sendBatteryPacket(otSockAddr *socket, uuid deviceId)
{
#if SHOW_DEBUG_STATS
  batteryPacketsSent += 1;
  printStats();
#endif

  deepSleepStart();
  return;
}