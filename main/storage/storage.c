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
