#ifndef _TIME_H
#define _TIME_H

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

#define US_TO_MS(us) us / 1000
#define MS_TO_SECONDS(ms) ms / 1000
#define MS_TO_MINUTES(ms) MS_TO_SECONDS(ms) / 60
#define US_TO_MINUTES(us) MS_TO_MINUTES(US_TO_MS(us))

int64_t timevalToMicro(struct timeval time);
struct timeval getCurrentTimeval();
struct timeval getFutureTimeval(int64_t seconds);
uint64_t timeDiffMs(struct timeval tv1, struct timeval tv2);
struct timeval randomTime(struct timeval tv1, struct timeval tv2);

int compareTimevals(const void* ptr1, const void* ptr2);

#endif // _TIME_H_