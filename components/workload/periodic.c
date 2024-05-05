/**
 * This file contains the worker thread that will do periodic sending
 * of CoAP requests.
*/
#include "workload.h"

void periodicSender(otSockAddr *socket) {
  sendRequest(Periodic, socket);
  otLogNotePlat("Sent scenario 1 packet.");
  otLogNotePlat("Will wait %d ms before sending next scenario 1 packet.",
                BATTERY_WAIT_TIME_MS);
  return;
}