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

DebugStats readDebugStats(nvs_handle_t handle)
{
  DebugStats stats;
  EmptyMemory(&stats, sizeof(DebugStats));
  nvsReadBlob(handle, NVS_DEBUG_STATS, &stats, sizeof(DebugStats));
  return stats;
}

void writeDebugStats(DebugStats *statsPtr, nvs_handle_t handle)
{
  nvsWriteBlob(handle, NVS_DEBUG_STATS, statsPtr, sizeof(DebugStats));
  return;
}

void printDebugStats(DebugStats stats, nvs_handle_t handle)
{
  uint64_t msElapsed = timeDiffMs(stats.powerOnTime, getCurrentTimeval());
  double minutesElapsed = MS_TO_MINUTES((double) msElapsed);

  otLogNotePlat("-----------------------------");
  otLogNotePlat("Time Elasped: ~%.3f minutes.", minutesElapsed);
  otLogNotePlat("Event packets sent: %d.", stats.eventPacketsSent);
  otLogNotePlat("Battery packets sent: %d.", stats.batteryPacketsSent);
  otLogNotePlat("-----------------------------");
  return;
}

void printSleepTimes(uint64_t batterySleepTime, uint64_t eventSleepTime)
{
  otLogNotePlat("-----------------------------");
  otLogNotePlat("Next Battery Sleep Time: %" PRIu64 ".", batterySleepTime);
  otLogNotePlat("Next Event Sleep Time: %" PRIu64 ".", eventSleepTime);
  if (eventSleepTime <= batterySleepTime)
  {
    otLogNotePlat("Will send an event packet in the next round.");
  }
  else
  {
    otLogNotePlat("Will send a battery lifetime packet in the next round.");
  }
  otLogNotePlat("-----------------------------");
  return;
}