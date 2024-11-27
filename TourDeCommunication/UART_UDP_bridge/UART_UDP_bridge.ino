#include <WiFi.h>
#include <WiFiUdp.h>
#include <string.h>

#define LED 13
#define BOUTON 14

#define UDP_PACKET_SIZE 8
#define UART_PACKET_SIZE 10
#define UART_START_CONDITION 0x24
#define CONTROL_TOWER_ID 0x03

//NETWORK CREDENTIALS
const char* SsidAP = "TourDeComEquipe3";
const char* PasswordAP = "TourDeComEquipe3";
const char* LocalIpAP = "192.168.27.1 ";
const char* GatewayAP = "192.168.27.1";  // Même que l'addresse IP, c'est voulu
const char* SubnetAP = "255.255.255.0";

//UDP related variables
WiFiUDP udp;
unsigned int ListenPort = 10024;          // ESP32 listens here
unsigned int VehiclePort = 10024;         // Send to Vehicle's listening port
const char* VehicleIP = "192.168.1.127";  //
char incomingPacket[255];                 // Buffer for incoming packets
char outgoingPacket[8];                   // Buffer for outgoing packets

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
  STMSerial.begin(115200, SERIAL_8N1, 16, 17);                // Baud rate, data bits, Rx pin (GPIO16), Tx pin (GPIO17)
  Serial.println("Serial Communication with STM32 started");  // Start indicator on debug serial port

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
}

void loop() {
  ReadUDP();
  ReadUART();
}

void ReadUDP() {
  static unsigned long UDPlastTime = 0;  // Stores the last time the function executed
  unsigned long UDPcurrentTime = millis();

  // Execute only if 100 millisecond have been elapsed
  if (UDPcurrentTime - UDPlastTime >= 100) {
    UDPlastTime = UDPcurrentTime;  // Update the last execution time

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
          Serial.println("Warning: Received UDP packet size does not match expected size.");
        }
      }
    }
  }
}

void WriteUDP() {
  // Send outgoing packet to the vehicle (or other destination)
  udp.beginPacket(VehicleIP, VehiclePort);                            // Vehicle's IP and port
  udp.write((const uint8_t*)outgoingPacket, sizeof(outgoingPacket));  // Send the packet
  udp.endPacket();                                                    // Finalize the packet

  Serial.println("Outgoing packet sent to the vehicle.");
}

void ReadUART() {
  static unsigned long UARTlastTime = 0;  // Stores the last time the function executed
  unsigned long UARTcurrentTime = millis();

  // Execute only if 100 millisecond have been elapsed
  if (UARTcurrentTime - UARTlastTime >= 100) {
    UARTlastTime = UARTcurrentTime;  // Update the last execution time

    if (STMSerial.available() == UART_PACKET_SIZE) {  // Check if expected amount of bytes has been received
      for (i = 0; i < UART_PACKET_SIZE; i++) {
        UARTFrameIN[i] = STMSerial.read();  // Read each received byte to UART incoming frame buffer
        Serial.print("Byte ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(UARTFrameIN[i], HEX);  // Print each received byte in hexadecimal format
      }
      if (UARTFrameIN[0] == UART_START_CONDITION) {  // Process data only if first byte is expected UART frame start condition
        ucCheckSum = 0;                              // Reset CheckSum value to ensure it is calculated correctly each time
        for (i = 2; i < (UART_PACKET_SIZE - 1); i++) {
          ucCheckSum += UARTFrameIN[i];  // Accumulates the received CheckSum
        }
        if (ucCheckSum == UARTFrameIN[UART_PACKET_SIZE - 1]) {  // Check if calculated checksum matches with received checksum
          for (i = 0; i < UDP_PACKET_SIZE; i++) {               // Copy received UART frame minus start condition, amount of bytes and checksum
            outgoingPacket[i] = UARTFrameIN[i + 2];
          }
          Serial.println("Received UART data, copied to outgoing UDP packet successfully");
          WriteUDP();
        } else {
          Serial.println("Warning: Received UART CheckSum does not match calculated CheckSum");
        }
      } else {
        Serial.println("Warning: Received UART start condition does not match expected start condition");
      }
    } else {
      Serial.println("Warning: Received UART frame size does not match expected size");
    }
  }
}

void WriteUART() {
  UARTFrameOUT[0] = UART_START_CONDITION;  // Start condition for UART frames
  UARTFrameOUT[1] = CONTROL_TOWER_ID;      // Identifier for Control Tower/Transports gestion unit on CAN network
  ucCheckSum = 0;                          // Reset stored checksum value to ensure it is calculated correctly each time

  for (i = 2; i < (UART_PACKET_SIZE - 1); i++) {  // Calculate CheckSum for outgoing UART data frame
    ucCheckSum = ucCheckSum + UARTFrameOUT[i];    // CheckSum does not include either the start condition of the identifier
  }
  UARTFrameOUT[UART_PACKET_SIZE - 1] = ucCheckSum;  //Checksum as the last byte of the outgoing UART data frame

  for (i = 0; i < UART_PACKET_SIZE; i++) {
    STMSerial.write(UARTFrameOUT[i]);  // Send each byte individually
  }
}