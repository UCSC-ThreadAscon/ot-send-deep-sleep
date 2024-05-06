#pragma once

#include "time.h"

#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdbool.h>
#include "esp_err.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_sleep.h"
#include "esp_timer.h"
#include "openthread/logging.h"

#define deepSleepStart()                      \
  otLogNotePlat("Going to deep sleep.");      \
  esp_deep_sleep_start();                     \

void initDeepSleepTimerMs(int wakeupTimeMs);
bool isDeepSleepWakeup(void);