#include "main.h"

bool noMoreEventsToSend(uint8_t eventsIndex)
{
  return eventsIndex >= NUM_EVENTS ? true : false;
}

void printPacketType(PacketSendType packetType)
{
  switch (packetType) {
    case (BatteryPacket):
      otLogNotePlat("Going to send a battery lifetime packet.");
      break;
    case (EventPacket):
      otLogNotePlat("Going to send an event packet.");
      break;
  }
  return;
}

DebugStats initDebugStats(struct timeval tvNow)
{
  DebugStats stats;
  stats.eventPacketsSent = 0;
  stats.batteryPacketsSent = 0;
  stats.powerOnTime = tvNow;
  return stats;
}

void printDebugStats(nvs_handle_t handle)
{
  DebugStats stats;
  EmptyMemory(&stats, sizeof(DebugStats));
  nvsReadBlob(handle, NVS_DEBUG_STATS, &stats, sizeof(DebugStats));

  uint64_t msElapsed = timeDiffMs(stats.powerOnTime, getCurrentTimeval());
  double minutesElapsed = MS_TO_MINUTES((double) msElapsed);

  otLogNotePlat("-----------------------------");
  otLogNotePlat("Time Elasped: ~%.3f minutes.", minutesElapsed);
  otLogNotePlat("Event packets sent: %d.", stats.eventPacketsSent);
  otLogNotePlat("Battery packets sent: %d.", stats.batteryPacketsSent);
  otLogNotePlat("-----------------------------");
  return;
}