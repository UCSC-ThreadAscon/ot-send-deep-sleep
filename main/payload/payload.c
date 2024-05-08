#include "payload.h"

EventPayload createEventPayload(uuid deviceId) {
  EventPayload newEvent;

  EmptyMemory(&newEvent, sizeof(EventPayload));

  newEvent.deviceId = deviceId;
  newEvent.eventOccured = true;

  return newEvent;
}

BatteryPayload createBatteryPayload(uuid deviceId) {
  BatteryPayload battery;

  EmptyMemory(&battery, sizeof(BatteryPayload));

  battery.deviceId = deviceId;
  battery.batteryLife = 100;
  return battery;
}