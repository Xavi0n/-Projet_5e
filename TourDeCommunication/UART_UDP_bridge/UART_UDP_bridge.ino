#include <WiFi.h>
#include <WiFiUdp.h>
#include <string.h>

#define LED 13
#define BOUTON 14

#define UDP_PACKET_SIZE 8
#define UART_PACKET_SIZE 10

//NETWORK CREDENTIALS
const char* SsidAP = "TourDeComEquipe3";
const char* PasswordAP = "TourDeComEquipe3";
const char* LocalIpAP = "192.168.27.1 ";
const char* GatewayAP = "192.168.27.1"; // Même que l'addresse IP, c'est voulu
const char* SubnetAP = "255.255.255.0";

//UDP related variables
WiFiUDP udp;
unsigned int ListenPort = 10024;          // ESP32 listens here
unsigned int VehiclePort = 10024;         // Send to Vehicle's listening port
const char* VehicleIP = "192.168.1.127";  //
char incomingPacket[255];                 // Buffer for incoming packets
char outgoingPacket[255];                 // Buffer for outgoing packets

//UART related variables
HardwareSerial STMSerial(1);  // Using UART1 to avoid conflict with debugging port, which is UART0
char UARTFrameIN[10];         // Buffer for incoming UART frames
char UARTFrameOUT[10];        // Buffer for outgoing UART frames
unsigned char ucCheckSum;     // Temporary variable for calculating CheckSums

//Misc variables
int i;  // Temp variable, mainly for for loops

void setup() {
  //Start serial comunication port with PC (via UART0, for debugging)
  Serial.begin(115200);

  //Start serial communication port with STM32 (via UART1, for data communication)
  STMSerial.begin(115200, SERIAL_8N1, 16, 17);                  // Baud rate, data bits, Rx pin (GPIO16), Tx pin (GPIO17)
  Serial.println("Serial Communication with STM32 started");    // Start indicator on debug serial port

  //INITIALISATIONS DES GPIO
  pinMode(LED, OUTPUT);
  pinMode(BOUTON, INPUT);

  //CONNEXION AU WIFI EN MODE ACCESS POINT
  WiFi.mode(WIFI_AP);
  WiFi.softAP(SsidAP, PasswordAP);
  delay(100);
  WiFi.softAPConfig(LocalIpAP, GatewayAP, SubnetAP);
  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());

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

  //
}

void loop() {
}


void ReadUDP() {
  static unsigned long lastTime = 0;  // Stores the last time the function executed
  unsigned long currentTime = millis();

  // Execute only if 100 millisecond have been elapsed
  if (currentTime - lastTime >= 100) {
    lastTime = currentTime;  // Update the last execution time

    // Check if a UDP packet has been received
    int packetSize = udp.parsePacket();

    if (packetSize) {  // If the packet size is greater than 0, data has been received
      int len = udp.read(incomingPacket, 255);
      if (len > 0) {
        // Print received data for debugging
        for (int i = 0; i < len; i++) {
          Serial.print("Byte ");
          Serial.print(i);
          Serial.print(": ");
          Serial.println(incomingPacket[i], HEX);  // Print in hexadecimal format
        }

        // Process the packet if it matches the expected size
        if (len == UDP_PACKET_SIZE) {
          for (int i = 0; i < UDP_PACKET_SIZE; i++) {
            UARTFrameOUT[i + 2] = incomingPacket[i];  // Write UDP data into the outgoing UART frame
          }
          WriteUART();  // Send data over UART
        } else {
          Serial.println("Warning: Packet size does not match expected size.");
        }
      }
    }
  }
}

void WriteUDP() {
}

void ReadUART() {
}

void WriteUART() {
  UARTFrameOUT[0] = 0x24;     // Start condition for UART frames
  UARTFrameOUT[1] = 0x03;     // Identifier for Control Tower/Transports gestion unit on CAN network
  ucCheckSum = 0;             // Reset stored checksum value to ensure it is calculated correctly each time

  for (i = 2; i < (UART_PACKET_SIZE-1); i++){     // Calculate CheckSum for outgoing UART data frame
    ucCheckSum = ucCheckSum + UARTFrameOUT[i];    // CheckSum does not include either the start condition of the identifier
  }
  UARTFrameOUT[UART_PACKET_SIZE-1] = ucCheckSum;  //Checksum as the last byte of the outgoing UART data frame
  
  for (i = 0; i < UART_PACKET_SIZE; i++){
    STMSerial.write(UARTFrameOUT[i]);             // Send each byte individually
  }
}