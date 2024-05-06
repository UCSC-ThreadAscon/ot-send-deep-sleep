#include "main.h"

/**
 * ---- CURRENT TO-DO ----
 * Send one event packet for each event in the "events" timeval array.
*/

void app_main(void)
{
  initAppMain();
  checkConnection(esp_openthread_get_instance());

  NvsData nvsData;
  otSockAddr socket;

  EmptyMemory(&nvsData, sizeof(NvsData));
  EmptyMemory(&socket, sizeof(otSockAddr));

  if (JUST_POWERED_ON)
  {
    onPowerOn(nvsData.events, &(nvsData.deviceId));
  }
  else
  {
    onWakeup(nvsData.events, &(nvsData.deviceId));
  }

  initDeepSleepTimerMs(BATTERY_WAIT_TIME_MS_TEST);

  coapStart();
  sendEventPacket(&socket, nvsData.deviceId);
  return;
}
