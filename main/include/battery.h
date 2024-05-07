#pragma once

#include "storage.h"

void nextBatteryWakeup(nvs_handle_t handle, struct timeval *batteryWakeup);
void printBatteryWakeup(struct timeval batteryWakeup);