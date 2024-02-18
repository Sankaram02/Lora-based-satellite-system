#define rainPin A1
#define DHT11PIN 4
#define MQ2Pin A0
#define SS_PIN 10
#define RST_PIN 9
#define BAND 868E6

#include <dht11.h>
#include <SPI.h>
#include <LoRa.h>

dht11 DHT11;
void setup() 
{
    Serial.begin(9600);
    pinMode(rainPin,INPUT); 
    pinMode(DHT11PIN,INPUT);
    while (!Serial);
    if (!LoRa.begin(BAND)) 
    {
      Serial.println("LoRa initialization failed. Check your wiring.");
      while (1);
  }
}

void loop() 
{
  int chk = DHT11.read(DHT11PIN);

  String rainVal=Rain();
  String  humVal=humidity();
  String tempval=temp();
  String airVal=airMQ2();

  LoRa.beginPacket();
  LoRa.print(rainVal);
  LoRa.print(humVal);
  LoRa.print(tempval);
  LoRa.print(airVal);
  delay(10);
  LoRa.endPacket();
  Serial.println("Message sent: " );
  delay(200);
  
}

int readSensor() {
  unsigned int sensorValue = analogRead(MQ2Pin);  // Read the analog value from sensor
  unsigned int outputValue = map(sensorValue, 0, 1023, 0, 255); // map the 10-bit data to 8-bit data
  return outputValue;             // Return analog moisture value
}

String Rain()
{
  int rainData=analogRead(rainPin);
  String isRain="";
  if(rainData>=0&&rainData<=299)
  {
    isRain="Full Rain";
  }
  if(rainData>=300&&rainData<=899)
  {
    isRain="Drizzle";
  }
  if(rainData>=900&&rainData<=1023)
  {
    isRain="No Rain";
  }
  Serial.println(isRain);
  return isRain;
}

String humidity()
{
  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);
  return " humidity is "+(String)DHT11.humidity;
}
String temp()
{
  Serial.print("Temperature  (C): ");
  Serial.println((float)DHT11.temperature, 2);
  return " Temp is "+(String)DHT11.temperature;
}

String airMQ2()
{
  Serial.print("Analog MQ2 output: ");
  int MQ2val = readSensor();
  Serial.println(MQ2val);
  return " air quality is "+(String)MQ2val;
}
