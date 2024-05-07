#include "main.h"

void app_main(void)
{
  initAppMain();
  checkConnection(esp_openthread_get_instance());

  struct timeval events[NUM_EVENTS];
  struct timeval batteryWakeup;
  uuid deviceId;
  otSockAddr socket;
  nvs_handle_t handle;

  EmptyMemory(events, sizeof(struct timeval));
  EmptyMemory(&deviceId, sizeof(uuid));
  EmptyMemory(&socket, sizeof(otSockAddr));
  EmptyMemory(&handle, sizeof(nvs_handle_t));
  EmptyMemory(&batteryWakeup, sizeof(struct timeval));

  openReadWrite(NVS_NAMESPACE, &handle);

  if (JUST_POWERED_ON)
  {
    onPowerOn(handle, events, &deviceId,
              &batteryWakeup);
  }
  else
  {
    wakeupInit(handle, events, &deviceId,
               &batteryWakeup);
  }

  onWakeup(handle, events, &deviceId, &socket,
           &batteryWakeup);
  nvs_close(handle);
  return;
}
