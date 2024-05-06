#pragma once

#include "dependencies.h"
#include "experiment.h"
#include "inline.h"
#include "print_macro.h"
#include "macro.h"

typedef enum type {
  Periodic = 1,
  APeriodic = 2
} type;

/* ---- Common API ---- */
void checkConnection(otInstance *aInstance);
void handleError(otError error, char* desc);
void printMeshLocalEid(otInstance *aInstance);

/** ---- CoAP Common API ---- */
uint16_t getPayloadLength(const otMessage *aMessage);
void getPayload(const otMessage *aMessage, void* buffer);
otSockAddr createSocket(const char *recvAddrString);
void coapStart(void);

/* ---- CoAP Client API ---- */
void request(otSockAddr *socket, void *payload, size_t payloadSize);

/* ---- CoAP Response Handler ---- */
void responseCallback(void *aContext,
                      otMessage *aMessage,
                      const otMessageInfo *aMessageInfo,
                      otError aResult);