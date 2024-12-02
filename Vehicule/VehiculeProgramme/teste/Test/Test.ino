
#include <Arduino.h>
#include "ServiceWiFiUdp.h"

char IncomingPacket[8];  // Buffer for incoming packets

// *************************************************************************************************
void setup(void) {
  Serial.begin(115200);
  vSetupToAccessPoint();
}

void loop() {
  vReadUDP();
  /*Serial.println('bonjour');
  delay(2000);
  Serial.println(IncomingPacket[0]);
  Serial.println(IncomingPacket[1]);
  Serial.println(IncomingPacket[2]);
  Serial.println(IncomingPacket[3]);
  Serial.println(IncomingPacket[4]);
  Serial.println(IncomingPacket[5]);
  Serial.println(IncomingPacket[6]);
  Serial.println(IncomingPacket[7]);*/
}
