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

EventPayload createEventPayload(uuid deviceId);
