#pragma once

#include "utilities.h"
#include "workload.h"
#include "init.h"
#include "time.h"
#include "sleep.h"
#include "storage.h"

#define NUM_EVENTS NUM_EVENTS_AIR_MONITOR

void initEventsArray(struct timeval *events,
                     struct timeval start,
                     struct timeval end);