/**
 * My Storage API is based upon the NVS example code programs
 * in the ESP-IDF Github repository:
 * https://github.com/espressif/esp-idf/tree/v5.2.1/examples/storage/nvs_rw_blob
 * https://github.com/espressif/esp-idf/tree/v5.2.1/examples/storage/nvs_rw_value
*/
#pragma once

#include "time.h"

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>

#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"

#define NVS_NAMESPACE "sed_nvs"
#define NVS_EVENTS_ARRAY "events"

void openReadWrite(const char *namespace, nvs_handle_t *handle);

void writeTimevalArray(nvs_handle_t *handle,
                       const char* key,
                       struct timeval *array,
                       size_t arraySize);