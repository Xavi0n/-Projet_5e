#ifndef SERVICEWIFIUDP_H
#define SERVICEWIFIUDP_H

#include <WiFiUdp.h>
#include "PiloteWiFi.h"  // Inclure la classe PiloteWiFi

class ServiceWiFiUdp {
public:
    ServiceWiFiUdp(PiloteWiFi& piloteWiFi, unsigned int localPort);
    void setupUDP();
    void loopUDP();

private:
    WiFiUDP udp;
    PiloteWiFi& piloteWiFi;  // Référence à l'instance PiloteWiFi
    unsigned int localPort;
    void toggleLED(const char* incomingPacket);
};

#endif
