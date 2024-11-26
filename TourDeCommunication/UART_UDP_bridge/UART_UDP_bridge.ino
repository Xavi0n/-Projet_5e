#include <WiFi.h>
#include <WiFiUdp.h>
#include <string.h>

#define LED 13
#define BOUTON 14

//NETWORK CREDENTIALS
const char* ssid = "Routeur627";
const char* ssid = "Routeur627";

//UDP settings
WiFiUDP udp;
unsigned int ListenPort = 10024;     // ESP32 listens here
unsigned int pcPort = 10025;         // Send to PC's listening port
const char* pcIP = "192.168.1.112";  // Replace with PC's IP
char incomingPacket[255];            // Buffer for incoming packets


void setup() {
  //INITIALISATIONS DES GPIO
  pinMode(LED, OUTPUT);
  pinMode(BOUTON, INPUT);
  bLedState = LOW;
  digitalWrite(LED, bLedState);

  //CONNEXION AU WIFI ET RECUPERATION DE L'ADDRESSE IP
  Serial.begin(115200);
  Serial.println("Connexion au routeur");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }

  //UNE FOIS CONNECTE, ECRIRE SUR LA CONSOLE L'ADDRESSE IP
  Serial.println("");
  Serial.println("Connecte au reseau");
  Serial.print("Addresse de l'ESP32: ");
  Serial.println(WiFi.localIP());

  // Start UDP and listen on esp32ListenPort
  udp.begin(ListenPort);
  Serial.printf("Now listening on UDP port %d\n", ListenPort);
}

void loop() {
  // Check if a UDP packet has been received
  int packetSize = udp.parsePacket();

  if (packetSize) {  // If the packet size is greater than 0, data has been received
    // Read the incoming packet
    int len = udp.read(incomingPacket, 255);
    if (len > 0) {
      for (int i = 0; i < len; i++) {       //Print received data to serial port
        Serial.print("Byte ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(incomingPacket[i], HEX); // Print in hexadecimal format
      }
    }
}


void ReadUDP(){

}

void WriteUDP(){
  
}

void ReadUART(){
  
}

void WriteUART(){
  
}