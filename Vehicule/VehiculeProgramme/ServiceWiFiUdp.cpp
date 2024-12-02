#include "ServiceWiFiUdp.h"
#include <WiFiUdp.h>

ServiceWiFiUdp::ServiceWiFiUdp(PiloteWiFi& piloteWiFi, unsigned int localPort)
    : piloteWiFi(piloteWiFi)  // Initialisation de la référence PiloteWiFi
{
    this->localPort = localPort;
}

void ServiceWiFiUdp::setupUDP() {
    // Assurez-vous que le Wi-Fi est connecté avant de démarrer l'UDP
    piloteWiFi.setupWiFi();
    udp.begin(localPort);
    Serial.print("UDP started on port ");
    Serial.println(localPort);
}

void ServiceWiFiUdp::loopUDP() {
    int packetSize = udp.parsePacket();
    if (packetSize > 0) {
        Serial.print("Received packet of size ");
        Serial.println(packetSize);
        
        char incomingPacket[255];
        int len = udp.read(incomingPacket, 255);
        if (len > 0) {
            incomingPacket[len] = 0;  // Null-terminate the string
        }
        Serial.print("Received: ");
        Serial.println(incomingPacket);

        // Toggle LED state if "TOGGLE_LED" message is received
        toggleLED(incomingPacket);
    }
    delay(10);
}

void ServiceWiFiUdp::toggleLED(const char* incomingPacket) {
    if (strcmp(incomingPacket, "TOGGLE_LED") == 0) {
        static bool ledState = false;
        ledState = !ledState;
        if (ledState) {
            digitalWrite(13, HIGH);
            Serial.println("LED is ON");
        } else {
            digitalWrite(13, LOW);
            Serial.println("LED is OFF");
        }
        
        const char* response = ledState ? "LED is ON" : "LED is OFF";
        udp.beginPacket(udp.remoteIP(), udp.remotePort());
        udp.write((uint8_t*)response, strlen(response));
        udp.endPacket();
    }
}
