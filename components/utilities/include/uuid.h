#pragma once

#include "hexdump.h"

#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#include "esp_random.h"
#include "openthread/logging.h"

/**
 * Bytes containing the UUID. A UUID will be 128 bits, in accordance
 * to RFC 4122:
 * https://datatracker.ietf.org/doc/html/rfc4122
*/
#define UUID_SIZE_BYTES 16

typedef struct uuid {
  uint8_t bytes[UUID_SIZE_BYTES];
} uuid;

void generateUUID(uuid *uuid);