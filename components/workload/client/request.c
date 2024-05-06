/**
 * All of the code in this file is based upon the both CoAP and CoAP secure
 * source code used as a part of the OpenThread codebase. The CoAP and
 * CoAP secure source files can be found at:
 * https://github.com/UCSC-ThreadAscon/openthread/tree/main/src/cli
*/
#include "workload.h"

otSockAddr createSocket(const char *recvAddrString)
{
  otSockAddr newSocket;
  otIp6Address recvAddr;

  EmptyMemory(&newSocket, sizeof(otSockAddr));
  EmptyMemory(&recvAddr, sizeof(otIp6Address));

  otIp6AddressFromString(recvAddrString, &recvAddr);

  newSocket.mAddress = recvAddr;
  newSocket.mPort = COAP_SOCK_PORT;

  return newSocket;
}

otMessage* createCoapMessage()
{
  otMessage *newMessage = otCoapNewMessage(OT_INSTANCE, NULL);
  if (newMessage == NULL) {
    otLogCritPlat("Failed to create CoAP request.");
    return NULL;
  }
  return newMessage;
}

inline void initCoapRequest(otMessage *aRequest, otMessageInfo *aMessageInfo)
{
  otError error = OT_ERROR_NONE;

  otCoapMessageInit(aRequest, OT_COAP_TYPE_CONFIRMABLE, OT_COAP_CODE_POST);
  otCoapMessageGenerateToken(aRequest, OT_COAP_DEFAULT_TOKEN_LENGTH);

  error = otCoapMessageAppendUriPathOptions(aRequest, BORDER_ROUTER_URI);
  HandleMessageError("append uri options", aRequest, error);
  return;
}

void request(otSockAddr *socket, void* payload, size_t payloadSize)
{
  otMessageInfo aMessageInfo;
  otMessage *aRequest;
  EmptyMemory(&aMessageInfo, sizeof(otMessageInfo));

  createMessageInfo(socket, &aMessageInfo);
  aRequest = createCoapMessage();

  return;
}