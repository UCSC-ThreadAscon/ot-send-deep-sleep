#include "main.h"

void moveToNextBatteryWakeup(nvs_handle_t handle, struct timeval *batteryWakeup,
                             struct timeval tvNow)
{
  batteryWakeup->tv_sec = tvNow.tv_sec + BATTERY_WAIT_TIME_SEC;
  nvsWriteBlob(handle, NVS_BATTERY_WAKEUP, batteryWakeup, sizeof(struct timeval));
  return;
}