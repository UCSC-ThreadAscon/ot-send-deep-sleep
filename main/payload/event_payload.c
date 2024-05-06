#pragma once

#include "main.h"
#include "payload.h"

#include <stdbool.h>

typedef struct EventPayload
{
  uuid deviceId;
  bool eventOccured;
}
EventPayload;