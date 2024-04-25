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

#define EXP_TIME_SECONDS 10800 // 10 minutes for debugging

/**
 * Second story motion sensor triggers once a year.
*/
#define NUM_EVENTS_SECOND_STORY 1

/**
 * Front door motion sensor tiggers 3 times a month, or
 * 12 * 5 = 36 times a year.
*/
#define NUM_EVENTS_FRONT_DOOR 36

/**
 * Air quality monitor triggers once a day every weekend, when
 * the humidifier recommends me to open my windows in the morning/afternoon
 * when I at home, AND when I am in Santa Cruz, which happens
 * 10 * 3 = 30 times a year.
 *
 * Thus, the air quality monitor will trigger 30 * 2 = 60 times a year.
*/
#define FIRST_STORY_BACKDOOR 60

#define NUM_EVENTS_TEST 10

#endif // EXPERIMENT_H