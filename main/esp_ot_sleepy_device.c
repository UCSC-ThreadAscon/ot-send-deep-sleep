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
#include "utilities.h"
#include "workload.h"

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

#if !SOC_IEEE802154_SUPPORTED
#error "Openthread sleepy device is only supported for the SoCs which have IEEE 802.15.4 module"
#endif

#define TAG "ot_send_deep_sleep"

static void create_config_network(otInstance *instance)
{
    otLinkModeConfig linkMode = { 0 };

    linkMode.mRxOnWhenIdle = false;
    linkMode.mDeviceType = false;
    linkMode.mNetworkData = false;

    if (otLinkSetPollPeriod(instance, POLL_PERIOD_MS) != OT_ERROR_NONE) {
        ESP_LOGE(TAG, "Failed to set OpenThread pollperiod.");
        abort();
    }
    ESP_LOGI(TAG, "Poll period is currently at %" PRIu32 ".",
             otLinkGetPollPeriod(instance));

    if (otThreadSetLinkMode(instance, linkMode) != OT_ERROR_NONE) {
        ESP_LOGE(TAG, "Failed to set OpenThread linkmode.");
        abort();
    }
    ESP_ERROR_CHECK(esp_openthread_auto_start(NULL));
}

static esp_netif_t *init_openthread_netif(const esp_openthread_platform_config_t *config)
{
    esp_netif_config_t cfg = ESP_NETIF_DEFAULT_OPENTHREAD();
    esp_netif_t *netif = esp_netif_new(&cfg);
    assert(netif != NULL);
    ESP_ERROR_CHECK(esp_netif_attach(netif, esp_openthread_netif_glue_init(config)));

    return netif;
}

static void otDeepSleepInit(int wakeupTimeMs)
{
    ESP_ERROR_CHECK(esp_sleep_enable_timer_wakeup(MS_TO_MICRO(wakeupTimeMs)));
}

static void ot_task_worker(void *aContext)
{
    esp_openthread_platform_config_t config = {
        .radio_config = ESP_OPENTHREAD_DEFAULT_RADIO_CONFIG(),
        .host_config = ESP_OPENTHREAD_DEFAULT_HOST_CONFIG(),
        .port_config = ESP_OPENTHREAD_DEFAULT_PORT_CONFIG(),
    };

    // Initialize the OpenThread stack
    ESP_ERROR_CHECK(esp_openthread_init(&config));

#if CONFIG_OPENTHREAD_LOG_LEVEL_DYNAMIC
    // The OpenThread log level directly matches ESP log level
    (void)otLoggingSetLevel(CONFIG_LOG_DEFAULT_LEVEL);
#endif
    esp_netif_t *openthread_netif;
    // Initialize the esp_netif bindings
    openthread_netif = init_openthread_netif(&config);
    esp_netif_set_default_netif(openthread_netif);

    create_config_network(esp_openthread_get_instance());

    // TX power must be set before starting the OpenThread CLI.
    setTxPower();

    // Run the main loop
    esp_openthread_launch_mainloop();

    // Clean up
    esp_openthread_netif_glue_deinit();
    esp_netif_destroy(openthread_netif);

    esp_vfs_eventfd_unregister();
    vTaskDelete(NULL);
}


#define NVS_PACKET_TYPE_KEY "workload_type"

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

    /**
     * ---- PSEUDOCODE ----
     *
     * When the device turns on:
     *    1. Works out the 4 wakeup times, records them in NVS.
     *    2. Generates UUID and records it in NVS.
     *    3. Run the onWakeup() algorithm.
     *
     * onWakeup():
     *    1. If woken up because of an event packet:
     *    2. Send an event packet.
     *    3. Go to sleep for the remainder of the 24 hours
     *
     *    Else:
     *      If next event is less than 24 hours away:
     *        Go to sleep for an appropriate amount of time.
     *      Else:
     *        Send a "I’m still here" packet.
     *        Go to sleep for 24 hours.
    */
    struct timeval tvNow = getCurrentTime(); 
    otLogNotePlat("The current time is %" PRId64 ".", timevalToMicro(tvNow));

    struct timeval tvExp = getFutureTimeval(EXP_TIME_SECONDS);
    otLogNotePlat("The time the experimental trail will end is %" PRId64 ".",
                  timevalToMicro(tvExp));

    otLogNotePlat("The time difference is %" PRIu64 " ms.", timeDiff(tvNow, tvExp));
    return;
}
