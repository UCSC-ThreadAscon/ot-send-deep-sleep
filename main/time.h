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

#define TO_MINUTES(ms) (ms / 1000) / 60

int64_t timevalToMicro(struct timeval time);
struct timeval getCurrentTimeval();
struct timeval getFutureTimeval(int64_t seconds);
uint64_t timeDiff(struct timeval tv1, struct timeval tv2);

#endif // _TIME_H_