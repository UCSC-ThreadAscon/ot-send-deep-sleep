#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

/**
 * Bytes containing the UUID. A UUID will be 128 bits, in accordance
 * to RFC 4122:
 * https://datatracker.ietf.org/doc/html/rfc4122
*/
typedef struct uuid {
  uint8_t bytes[16];
} uuid;

#define UUID_SIZE 16                                // in bytes
#define UUID_STRING_SIZE UUID_SIZE * sizeof(char)   // string size when printing UUID

#include "esp_random.h"
#include "openthread/logging.h"