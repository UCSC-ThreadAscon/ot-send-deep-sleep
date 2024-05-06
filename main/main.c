#include "main.h"

#define BATTERY_WAIT_TIME_MS_TEST 5000

/**
 * ---- CURRENT TO-DO ----
 * Send one event packet for each evnt in the "events" timeval array.
*/

void app_main(void)
{
  initAppMain();
  checkConnection(esp_openthread_get_instance());

  struct timeval events[NUM_EVENTS];
  uuid deviceId;
  otSockAddr socket;

  EmptyMemory(events, EVENTS_ARRAY_SIZE);
  EmptyMemory(&deviceId, sizeof(uuid));
  EmptyMemory(&socket, sizeof(otSockAddr));

  if (JUST_POWERED_ON)
  {
    onPowerOn(events, &deviceId);
  }
  else
  {
    onDeepSleepWakeup(events, &deviceId);
  }

  initDeepSleepTimerMs(BATTERY_WAIT_TIME_MS_TEST);

  coapStart();
  sendEventPacket(&socket, deviceId);
  return;
}
