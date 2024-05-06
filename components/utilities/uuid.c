#include "uuid.h"

void generateUUID(uuid *uuid) {
  uint32_t *uuidWords = (uint32_t *) uuid->bytes;

  for (int i = 0; i < UUID_SIZE_WORDS; i++)
  {
    uuidWords[i] = esp_random();
  }
  return;
}

#define ONE_BYTE_HEX_STRING sizeof(char) * 2

void printBytesUUID(uuid *uuid) {
  uint8_t *uuidBytes = uuid->bytes;
  char uuidString[32];

  for (int byte = 0; byte < UUID_SIZE_BYTES; byte += 1) {
    char *string = &(uuidString[byte * ONE_BYTE_HEX_STRING]);
    sprintf(string, "%X", uuidBytes[byte]);
  }

  otLogNotePlat("The UUID is 0x%s.", uuidString);
  return;
}