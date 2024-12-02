/**************************************************************************************************
//  Nom du fichier : ServiceWiFiUdp.cpp
//  Auteur : Naomie Dion
//  Date de création : 2 Decembre 2024
//  Version 1.1
***************************************************************************************************/
// *************************************************************************************************
//  INCLUDES
// *************************************************************************************************
#include "ServiceWiFiUdp.h"
#include <WiFiUdp.h>
#include <WiFi.h>

// *************************************************************************************************
//  CONSTANTES
// *************************************************************************************************
#define UDP_PACKET_SIZE 8

// *************************************************************************************************
// VARIABLES GLOBALES
// *************************************************************************************************
//NETWORK CREDENTIALS
const char* SsidAP = "TourDeComEquipe3";
const char* PasswordAP = "TourDeComEquipe3";
// UDP settings
WiFiUDP udp;
unsigned int ListenPort = 10024;          // ESP32 listens here
unsigned int WritePort = 10025;  
const char* AccessPointIP = "192.168.27.1";  //
//char IncomingPacket[8];                 // Buffer for incoming packets
char OutgoingPacket[8];                   // Buffer for outgoing packets

// *************************************************************************************************
//  FONCTIONS
// *************************************************************************************************
void vSetupToAccessPoint(void)
{
  // Connection sur le réseau WIFI
   Serial.print("Connecting to ");
   Serial.println(SsidAP);
   WiFi.begin(SsidAP, PasswordAP);
   while (WiFi.status() != WL_CONNECTED)
   {
     delay(500);
    Serial.print(".");
   }
   // Envoie sur le port série, l'adresse IP
   Serial.println("");
   Serial.println("WiFi connected.");
   Serial.println("IP address: ");
   Serial.println(WiFi.localIP());
  
  // Start UDP on the local port
  udp.begin(ListenPort);
  Serial.print("UDP started on port ");
  Serial.println(ListenPort);
}

void vReadUDP(void) 
{
 // Receive UDP packet
  int packetSize = udp.parsePacket();
  Serial.println(packetSize);
  if (packetSize > 0) 
  {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    
    int len = udp.read(IncomingPacket, 8);  // Read the packet into the buffer
    Serial.print("Received: ");
    Serial.println(IncomingPacket);
  }
}

void vWriteUDP(void) 
{
  // Send outgoing packet to the vehicle (or other destination)
  udp.beginPacket(AccessPointIP, WritePort);                            // Vehicle's IP and port
  udp.write((const uint8_t*)OutgoingPacket, sizeof(OutgoingPacket));     // Send the packet
  udp.endPacket();                                                      // Finalize the packet
}
