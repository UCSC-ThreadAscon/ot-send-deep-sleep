#pragma once

#include "time.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "esp_err.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_sleep.h"
#include "esp_timer.h"
#include "esp_ot_sleepy_device_config.h"
#include "driver/uart.h"
#include "openthread/logging.h"

void initDeepSleepTimerMs(int wakeupTimeMs);