#include "main.h"

void nextBatteryWakeup(nvs_handle_t handle, struct timeval *batteryWakeup)
{
  batteryWakeup->tv_sec = getCurrentTimeval().tv_sec + BATTERY_WAIT_TIME_SEC;
  nvsWriteBlob(handle, NVS_BATTERY_WAKEUP, batteryWakeup, sizeof(struct timeval));
  return;
}

void printBatteryWakeup(struct timeval batteryWakeup)
{
  int64_t micro = toMicro(batteryWakeup);
  double minutes = US_TO_MINUTES((double) micro);
  otLogNotePlat("The next battery wakeup will be in %.3f minutes.", minutes);
  return;
}