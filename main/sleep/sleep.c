#include "sleep.h"

void initDeepSleepTimerMs(int wakeupTimeMs)
{
    ESP_ERROR_CHECK(esp_sleep_enable_timer_wakeup(MS_TO_US(wakeupTimeMs)));
}
