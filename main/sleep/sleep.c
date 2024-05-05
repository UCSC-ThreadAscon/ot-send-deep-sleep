#include "sleep.h"

void initDeepSleepTimerMs(int wakeupTimeMs)
{
    ESP_ERROR_CHECK(esp_sleep_enable_timer_wakeup(MS_TO_US(wakeupTimeMs)));
}

bool isDeepSleepWakeup(void) {
  return esp_sleep_get_wakeup_cause() != ESP_SLEEP_WAKEUP_UNDEFINED ?
         true : false;
}