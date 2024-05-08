#pragma once

#include "init.h"
#include "uuid.h"

void initEventsArray(struct timeval *events,
                     struct timeval start,
                     struct timeval end);
void sendEventPacket(otSockAddr *socket, uuid deviceId, nvs_handle_t handle);
void sendBatteryPacket(otSockAddr *socket, uuid deviceId, nvs_handle_t handle);

void printEventsIndex(uint8_t index);
void printEventsArray(struct timeval *events, int numEvents);
void printEventMinutes(int eventNum, struct timeval time);