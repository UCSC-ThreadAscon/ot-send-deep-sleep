#include "payload.h"

EventPayload createEventPayload(uuid deviceId) {
  EventPayload newEvent;

  EmptyMemory(&newEvent, sizeof(EventPayload));

  newEvent.deviceId = deviceId;
  newEvent.eventOccured = true;

  return newEvent;
}
