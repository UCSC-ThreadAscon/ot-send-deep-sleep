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