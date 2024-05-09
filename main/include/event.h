#pragma once

#include "init.h"
#include "uuid.h"

void initEventsArray(struct timeval *events);

void printEventsIndex(uint8_t index);
void printEventsArray(struct timeval *events, int numEvents);
void printEventMinutes(int eventNum, struct timeval time);