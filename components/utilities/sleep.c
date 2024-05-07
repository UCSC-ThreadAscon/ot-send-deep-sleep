#include "sleep.h"

static int wakeupTimeMs;

void initDeepSleepTimerMs(int timeMs)
{
  wakeupTimeMs = timeMs;
  ESP_ERROR_CHECK(esp_sleep_enable_timer_wakeup(MS_TO_US(timeMs)));
}

bool isDeepSleepWakeup(void) {
  return esp_sleep_get_wakeup_cause() != ESP_SLEEP_WAKEUP_UNDEFINED ?
         true : false;
}

void deepSleepStart() {
  double wakeupTimeMins = MS_TO_MINUTES( (double) wakeupTimeMs);
  otLogNotePlat("Going to deep sleep for %d ms, or ~%.3f minutes.",
                wakeupTimeMs, wakeupTimeMins);
  esp_deep_sleep_start();
  return;
}