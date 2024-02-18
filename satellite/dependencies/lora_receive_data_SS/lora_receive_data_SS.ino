#include <SPI.h>
#include <LoRa.h>
#include <SoftwareSerial.h>

#define SS_PIN 10
#define RST_PIN 9
#define BAND 868E6 // Change this to match your LoRa module's frequency

SoftwareSerial myserial(2,3);//rx,tx
String receivedMessage = "";
char* cString;

void setup() {
  Serial.begin(9600);
  myserial.begin(9600);
  while (!Serial);

  // Initialize LoRa module
  if (!LoRa.begin(BAND)) {
    Serial.println("LoRa initialization failed. Check your wiring.");
    while (1);
  }
}
void loop()
{
  if (LoRa.parsePacket()) 
  {
    String receivedMessage = "";
    while (LoRa.available()) 
    {
      receivedMessage += (char)LoRa.read();
    }
    Serial.println("Message received: " + receivedMessage);
//    char* cString = (char*) malloc(sizeof(char)*(receivedMessage.length() + 1));
//    receivedMessage.toCharArray(cString, receivedMessage.length() + 1);
//    myserial.write(cString);
    }
}
