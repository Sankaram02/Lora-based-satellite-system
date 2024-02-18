#include <SPI.h>
#include <LoRa.h>

#define SS_PIN 10
#define RST_PIN 9
#define BAND 868E6 // Change this to match your LoRa module's frequency

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Initialize LoRa module
  if (!LoRa.begin(BAND)) {
    Serial.println("LoRa initialization failed. Check your wiring.");
    while (1);
  }
}
void loop() {
  // Send data
  String message = "Hello, World!";
  LoRa.beginPacket();
  LoRa.print(message);
  LoRa.endPacket();
  Serial.println("Message sent: " + message);
  delay(2000); // Send data every 2 seconds

  // Receive data
  if (LoRa.parsePacket()) {
    String receivedMessage = "";
    while (LoRa.available()) {
      receivedMessage += (char)LoRa.read();
    }
    Serial.println("Message received: " + receivedMessage);
  }
}
