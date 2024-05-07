#include "main.h"

bool noMoreEventsToSend(uint8_t eventsIndex)
{
  return eventsIndex >= NUM_EVENTS ? true : false;
}

void eventPacketsStats(uint8_t eventsIndex)
{
  if (!noMoreEventsToSend(eventsIndex))
  {
    otLogNotePlat("Sent %" PRIu8 " Event Packet(s) so far.", eventsIndex);
  }
  else
  {
    otLogNotePlat("Sent all Event Packets.");
  }
  return;
}