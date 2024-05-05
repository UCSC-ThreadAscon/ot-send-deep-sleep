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
void otDeepSleepInit(int wakeupTimeMs);
void ot_task_worker(void *aContext);

#endif // _INIT_H_