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

static RTC_DATA_ATTR struct timeval s_sleep_enter_time;

static void create_config_network(otInstance *instance)
{
    otLinkModeConfig linkMode = { 0 };

    linkMode.mRxOnWhenIdle = false;
    linkMode.mDeviceType = false;
    linkMode.mNetworkData = false;

    if (otLinkSetPollPeriod(instance, CONFIG_POLL_PERIOD) != OT_ERROR_NONE) {
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

/**
 * Within this function, we print the reason for the wake-up and configure the method of waking up from deep sleep.
 * This example provides support for two wake-up sources from deep sleep: RTC timer and GPIO.
 * 
 * The one-shot timer will start when the device transitions to the CHILD state for the first time.
 * After a 5-second delay, the device will enter deep sleep.
*/
static void ot_deep_sleep_init(void)
{
    // Print the wake-up reason:
    struct timeval now;
    gettimeofday(&now, NULL);
    int sleep_time_ms = (now.tv_sec - s_sleep_enter_time.tv_sec) * 1000 + (now.tv_usec - s_sleep_enter_time.tv_usec) / 1000;
    esp_sleep_wakeup_cause_t wake_up_cause = esp_sleep_get_wakeup_cause();
    switch (wake_up_cause) {
    case ESP_SLEEP_WAKEUP_TIMER: {
        ESP_LOGI(TAG, "Wake up from timer. Time spent in deep sleep and boot: %dms", sleep_time_ms);
        break;
    }
    case ESP_SLEEP_WAKEUP_EXT1: {
        ESP_LOGI(TAG, "Wake up from GPIO. Time spent in deep sleep and boot: %dms", sleep_time_ms);
        break;
    }
    case ESP_SLEEP_WAKEUP_UNDEFINED:
    default:
        ESP_LOGI(TAG, "Not a deep sleep reset");
        break;
    }

    // Set the methods of how to wake up:
    // 1. RTC timer waking-up
    const int wakeup_time_ms = CONFIG_POLL_PERIOD;
    ESP_LOGI(TAG, "Enabling timer wakeup, %dms\n", wakeup_time_ms);
    ESP_ERROR_CHECK(esp_sleep_enable_timer_wakeup(MS_TO_MICRO(wakeup_time_ms)));

    // 2. GPIO waking-up
#if CONFIG_IDF_TARGET_ESP32C6
    // For ESP32C6 boards, RTCIO only supports GPIO0~GPIO7
    // GPIO7 pull down to wake up
    const int gpio_wakeup_pin = 7;
#elif CONFIG_IDF_TARGET_ESP32H2
    // You can wake up by pulling down GPIO9. On ESP32H2 development boards, the BOOT button is connected to GPIO9.
    // You can use the BOOT button to wake up the boards directly.
    const int gpio_wakeup_pin = 9;
#endif
    const uint64_t gpio_wakeup_pin_mask = 1ULL << gpio_wakeup_pin;
    // The configuration mode depends on your hardware design.
    // Since the BOOT button is connected to a pull-up resistor, the wake-up mode is configured as LOW.
    const uint64_t ext_wakeup_mode = 0;
    ESP_ERROR_CHECK(esp_sleep_enable_ext1_wakeup_io(gpio_wakeup_pin_mask, ext_wakeup_mode));

    // Also these two GPIO configurations are also depended on the hardware design.
    // The BOOT button is connected to the pull-up resistor, so enable the pull-up mode and disable the pull-down mode.

    // Notice: if these GPIO configurations do not match the hardware design, the deep sleep module will enable the GPIO hold
    // feature to hold the GPIO voltage when enter the sleep, which will ensure the board be waked up by GPIO. But it will cause
    // 3~4 times power consumption increasing during sleep.
    ESP_ERROR_CHECK(gpio_pullup_en(gpio_wakeup_pin));
    ESP_ERROR_CHECK(gpio_pulldown_dis(gpio_wakeup_pin));
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

    ot_deep_sleep_init();

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

    /** ---- CoAP Client Code ---- */
    checkConnection(OT_INSTANCE);
    printMeshLocalEid(OT_INSTANCE);

    otError error = otCoapStart(OT_INSTANCE, COAP_SOCK_PORT);

    if (error != OT_ERROR_NONE) {
      otLogCritPlat("Failed to start COAP server.");
    } else {
      otLogNotePlat("Started CoAP server at port %d.", COAP_SERVER_PORT);
    }

    otSockAddr socket;
    otIp6Address server;

    EmptyMemory(&socket, sizeof(otSockAddr));
    EmptyMemory(&server, sizeof(otIp6Address));

    otIp6AddressFromString(CONFIG_SERVER_IP_ADDRESS, &server);
    socket.mAddress = server;
    socket.mPort = COAP_SERVER_PORT;

    /**
     * Sending of periodic packets will be handled by separate
     * worker thread.
    */
    xTaskCreate(periodicWorker, "periodic_client", 10240,
                (void *) &socket, 5, NULL);

    /**
     * Sending of aperiodic packets is handled below.
    */
    while (true) {
      sendRequest(APeriodic, &socket);

      uint32_t nextWaitTime = aperiodicWaitTimeMs();
      otLogNotePlat(
        "Will wait %" PRIu32 " ms before sending next aperiodic CoAP request.",
        nextWaitTime
      );

      TickType_t lastWakeupTime = xTaskGetTickCount();

      /**
       * If quotient "nextWaitTime" < "portTICK_PERIOD_MS", then
       * MS_TO_TICKS(nextWaitTime) == 0, causing `vTaskDelayUntil()`
       * to crash. When this happens, set the delay to be exactly
       * `portTICK_PERIOD_MS`.
      */
      TickType_t nextWaitTimeTicks =
        MS_TO_TICKS(nextWaitTime) == 0 ? portTICK_PERIOD_MS :
          MS_TO_TICKS(nextWaitTime);

      vTaskDelayUntil(&lastWakeupTime, nextWaitTimeTicks);
     }

    return;
}
