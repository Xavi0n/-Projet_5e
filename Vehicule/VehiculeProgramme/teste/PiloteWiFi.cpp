#include "PiloteWiFi.h"
#include <WiFi.h>

PiloteWiFi::PiloteWiFi(const char* ssid, const char* password) 
{
    this->ssid = ssid;
    this->password = password;
}

void PiloteWiFi::setupWiFi()
{
    Serial.begin(19200);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

WiFiClient PiloteWiFi::getClient() 
{
    return WiFiClient();
}

