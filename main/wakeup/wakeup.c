#include "main.h"

void onWakeup(struct timeval *events, uuid *deviceId)
{
  wakeupInit(events, deviceId);
  return;
}