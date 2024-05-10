#include "main.h"
#include "assert.h"

void wakeupInit(nvs_handle_t handle,
                struct timeval *events,
                uuid *deviceId,
                Data *dataPtr)
{
  nvsReadBlob(handle, NVS_EVENTS_ARRAY, events, EVENTS_ARRAY_SIZE);
  nvsReadBlob(handle, NVS_UUID, deviceId, UUID_SIZE_BYTES);
  nvsReadBlob(handle, NVS_DATA, dataPtr, sizeof(Data));

#if NVS_DEBUG
  printEventsArray(events, NUM_EVENTS);
#endif

  return;
}

static inline void incrementEventsIndex(nvs_handle_t handle,
                                        uint8_t currentEventsIndex)
{
  currentEventsIndex += 1;
  nvsWriteByteUInt(handle, NVS_EVENTS_INDEX, currentEventsIndex);
  return;
}

uint64_t getNextSleepMicro(struct timeval *events,
                           uint8_t eventsIndex)
{
    struct timeval tvNextEvent = events[eventsIndex];
    return timeDiffMicro(getTimevalNow(), tvNextEvent);
}

void onWakeup(nvs_handle_t handle,
              struct timeval *events,
              uuid *deviceId,
              otSockAddr *socket,
              Data *data)
{
  uint8_t eventsIndex = nvsReadByteUInt(handle, NVS_EVENTS_INDEX);
  Status prevStatus = data->status;

  if (!noMoreEventsToSend(eventsIndex))
  {
    /**
     * STEP 1: Get sleep times for event and battery packet.
    */
    uint64_t eventSleepMicro = getNextSleepMicro(events, eventsIndex);
    uint64_t batterySleepTime = data->batterySleepTime;

#if TIME_DIFF_DEBUG
    printSleepTimes(eventSleepMicro, batterySleepTime);
#endif

    /**
     *  STEP 2(a): If event packet is less, then you will send event packet
     *             on next wakeup.
     *
     *             battery sleep time in NVS =
     *                battery sleep time - event packet sleep time.
    */
    if (eventSleepMicro < batterySleepTime) {
      initDeepSleepTimerMicro(eventSleepMicro);
      incrementEventsIndex(handle, eventsIndex);

      data->status = Event;
      data->batterySleepTime = batterySleepTime - eventSleepMicro;
    }

    /**
     *  STEP 2(b): If battery packet is less than, you will send a battery
     *             packet on next wakeup.
     *
     *             battery sleep time in NVS = reset to 30 seconds.
    */
   else if (eventSleepMicro > batterySleepTime) {
      initDeepSleepTimerMicro(batterySleepTime);

      data->status = Battery;
      data->batterySleepTime = BATTERY_WAIT_TIME_MICRO;
   }

    /**
     * STEP 3: Update Data struct with new status and battery sleep time.
     *         Write it to NVS.
    */
    nvsWriteBlob(handle, NVS_DATA, data, sizeof(Data));
  }
  else {
    /**
     * Send only battery lifetime packets.
    */
    initDeepSleepTimerMicro(data->batterySleepTime);
    data->status = Battery;
    data->batterySleepTime = BATTERY_WAIT_TIME_MICRO;
    nvsWriteBlob(handle, NVS_DATA, data, sizeof(Data));
  }

  /**
   * STEP 4: Whatever you decided on the previous wakeup,
   *         send that type of packet.
  */
  coapStart();
  if (prevStatus == Event) {
    sendEventPacket(socket, *deviceId);
  }
  else if ((prevStatus == PowerOn) ||
           (prevStatus == Battery)) {
    sendBatteryPacket(socket, *deviceId);
  }

#if EVENT_DEBUG
  eventPacketsStats(eventsIndex);
#endif

  return;
}