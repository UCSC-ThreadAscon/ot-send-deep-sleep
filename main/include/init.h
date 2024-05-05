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
#ifndef _INIT_H_
#define _INIT_H_

#include "utilities.h"
#include "workload.h"

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

void create_config_network(otInstance *instance);
esp_netif_t *init_openthread_netif(const esp_openthread_platform_config_t *config);
void ot_task_worker(void *aContext);
void initAppMain();

#endif // _INIT_H_