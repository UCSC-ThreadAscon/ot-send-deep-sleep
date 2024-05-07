#include "main.h"

void app_main(void)
{
  initAppMain();
  checkConnection(esp_openthread_get_instance());

  struct timeval events[NUM_EVENTS];
  uuid deviceId;
  otSockAddr socket;
  nvs_handle_t handle;

  EmptyMemory(events, sizeof(struct timeval));
  EmptyMemory(&deviceId, sizeof(uuid));
  EmptyMemory(&socket, sizeof(otSockAddr));
  EmptyMemory(&handle, sizeof(nvs_handle_t));

  openReadWrite(NVS_NAMESPACE, &handle);

  if (JUST_POWERED_ON)
  {
    onPowerOn(handle, events, &deviceId);
  }
  else
  {
    wakeupInit(handle, events, &deviceId);
  }

  onWakeup(handle, events, &deviceId);
  nvs_close(handle);

  coapStart();
  sendEventPacket(&socket, deviceId);
  return;
}
