#pragma once

#include "init.h"
#include "uuid.h"

#include <stdbool.h>

typedef struct EventPayload
{
  uuid deviceId;
  bool eventOccured;
}
EventPayload;

typedef struct BatteryPayload
{
  uuid deviceId;
  uint8_t batteryLife;
}
BatteryPayload;

EventPayload createEventPayload(uuid deviceId);
