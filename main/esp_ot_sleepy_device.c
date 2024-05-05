/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 *
 * OpenThread Command Line Example
 *
 * This example code is in the Public Domain (or CC0 licensed, at your option.)
 *
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
*/
#include "workload.h"
#include "init.h"
#include "time.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "esp_err.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_sleep.h"
#include "esp_timer.h"
#include "esp_openthread.h"
#include "esp_openthread_netif_glue.h"
#include "esp_ot_sleepy_device_config.h"
#include "esp_vfs_eventfd.h"
#include "nvs_flash.h"
#include "driver/rtc_io.h"
#include "driver/uart.h"
#include "openthread/logging.h"
#include "openthread/thread.h"


#define NVS_PACKET_TYPE_KEY "workload_type"

int compare (const void* ptr1, const void* ptr2) {
  int64_t *numPtr1 = (int64_t *) ptr1;
  int64_t *numPtr2 = (int64_t *) ptr2;
  int64_t num1 = *numPtr1;
  int64_t num2 = *numPtr2;

  if (num1 < num2) {
    return -1;
  }
  else if (num1 == num2) {
    return 0;
  }
  else {
    return 1;
  }
}

void app_main(void)
{
  // Used eventfds:
  // * netif
  // * ot task queue
  // * radio driver
  esp_vfs_eventfd_config_t eventfd_config = {
      .max_fds = 3,
  };

  ESP_ERROR_CHECK(nvs_flash_init());
  ESP_ERROR_CHECK(esp_event_loop_create_default());
  ESP_ERROR_CHECK(esp_netif_init());
  ESP_ERROR_CHECK(esp_vfs_eventfd_register(&eventfd_config));

  xTaskCreate(ot_task_worker, "ot_power_save_main", 4096, NULL, 5, NULL);

  struct timeval tvNow = getCurrentTimeval(); 
  struct timeval tvExp = getFutureTimeval(EXP_TIME_SECONDS);

  int64_t eventsUs[NUM_EVENTS_TEST];
  EmptyMemory(eventsUs, sizeof(eventsUs));

    for (int i = 0; i < NUM_EVENTS_TEST; i++) {
      struct timeval tvRandom = randomTime(tvNow, tvExp);
      int64_t randomTimeMicro = timevalToMicro(tvRandom);
      eventsUs[i] = randomTimeMicro;
    }

    qsort(&eventsUs, NUM_EVENTS_TEST, sizeof(int64_t), compare);

    for (int i = 0; i < NUM_EVENTS_TEST; i++) {
      otLogNotePlat("The next event will be in approximately %" PRId64 " minutes.",
                    US_TO_MINUTES(eventsUs[i]));
    }

    return;
}
