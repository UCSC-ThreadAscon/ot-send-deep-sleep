#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <stdbool.h>

#define POLL_PERIOD_MS CONFIG_POLL_PERIOD

/**
 * This part of the header defines the constants to be used in the experiments,
 * in accordance to the Experimental Setup document:
 * https://docs.google.com/document/d/15ahJuklkLitBmBDbUqnAVBdkny0B3X3-V_8ODYbE8xw/edit?usp=sharing
*/
#define PERIODIC_URI "periodic"
#define APERIODIC_URI "aperiodic"

#define APERIODIC_PAYLOAD_SIZE 4
#define PERIODIC_PAYLOAD_SIZE 216

#define PERIODIC_WAIT_TIME_MS 1000 * 30 // 30 seconds

#define EXP_TIME_SECONDS 10980 // ~183 minutes

#define NUM_EVENTS_FRONT_DOOR 36
#define NUM_EVENTS_AIR_MONITOR 10
#define NUM_EVENTS_SECOND_STORY 1

#endif // EXPERIMENT_H