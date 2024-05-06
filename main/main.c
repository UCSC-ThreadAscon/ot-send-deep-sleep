#include "main.h"

/**
 * ---- CURRENT TO-DO ----
 * 1. Create an index of the current event packet to send, and update it
 *    upon every wakeup.
 * 2. Use that index, and the API you created to manage it, to determine
 *    how long the device should sleep before sending the next event packet.
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
