#pragma once

#include "storage.h"

void moveToNextBatteryWakeup(nvs_handle_t handle, struct timeval *batteryWakeup,
                             struct timeval tvNow);