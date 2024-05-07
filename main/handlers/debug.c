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
