#include "uuid.h"

void generateUUID(uuid *uuid) {
  esp_fill_random(uuid->bytes, UUID_SIZE_BYTES);
  return;
}

void printUUID(uuid *uuid) {
  uint32_t test = esp_random();

  hexDump(&test, sizeof(uint32_t), "Sleepy End Device UUID");
  return;
}