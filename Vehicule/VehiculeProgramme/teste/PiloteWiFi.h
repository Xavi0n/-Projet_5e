#ifndef PILOTEWIFI_H
#define PILOTEWIFI_H

#include <WiFi.h>

class PiloteWiFi 
{
public:
    PiloteWiFi(const char* ssid, const char* password);
    void setupWiFi();
    WiFiClient getClient();

private:
    const char* ssid;
    const char* password;
};

#endif