/**
 * My Storage API is based upon the NVS example code programs
 * in the ESP-IDF Github repository:
 * https://github.com/espressif/esp-idf/tree/v5.2.1/examples/storage/nvs_rw_blob
 * https://github.com/espressif/esp-idf/tree/v5.2.1/examples/storage/nvs_rw_value
*/
#include "storage.h"

void openReadWrite(const char *namespace, nvs_handle_t *handle) {
  ESP_ERROR_CHECK(nvs_open(namespace, NVS_READWRITE, handle));
  return;
}

void nvsWriteArray(nvs_handle_t handle,
                   const char* key,
                   void *array,
                   size_t arraySize)
{
  ESP_ERROR_CHECK(nvs_set_blob(handle, key, array, arraySize));
  ESP_ERROR_CHECK(nvs_commit(handle));
  return;
}

void nvsReadArray(nvs_handle_t handle,
                  const char* key,
                  void *array,
                  size_t arraySize)
{
  ESP_ERROR_CHECK(nvs_get_blob(handle, key, array, &arraySize));
  return;
}

uint8_t nvsReadByteUInt(nvs_handle_t handle, const char* key) {
  uint8_t numberRead = 0;
  ESP_ERROR_CHECK(nvs_get_u8(handle, key, &numberRead));
  return numberRead;
}

void nvsWriteByteUInt(nvs_handle_t handle, const char* key, uint8_t number) {
  ESP_ERROR_CHECK(nvs_set_u8(handle, key, number));
  ESP_ERROR_CHECK(nvs_commit(handle));
  return;
}
