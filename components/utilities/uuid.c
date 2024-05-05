#include "uuid.h"

void generateUUID(uuid *uuid) {
  esp_fill_random(uuid->bytes, UUID_SIZE_BYTES);
  return;
}

void printUUID(uuid *uuid) {
  hexDump(uuid->bytes, UUID_SIZE_BYTES, "Sleepy End Device UUID");
  return;
}