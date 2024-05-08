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

void printDebugStats(DebugStats stats)
{
  uint64_t msElapsed = timeDiffMs(stats.powerOnTime, getCurrentTimeval());
  double minutesElapsed = MS_TO_MINUTES((double) msElapsed);

  otLogNotePlat("Time Elasped: ~%.3f minutes.", minutesElapsed);
  otLogNotePlat("Event packets sent: %d.", stats.eventPacketsSent);
  otLogNotePlat("Battery packets sent: %d.", stats.batteryPacketsSent);
  return;
}