#define rainPin A1
#define DHT11PIN 4
#define MQ2Pin A0

#include <dht11.h>

dht11 DHT11;
void setup() 
{
    Serial.begin(9200);
    pinMode(rainPin,INPUT); 
    pinMode(DHT11PIN,INPUT);
}

void loop() 
{
  int chk = DHT11.read(DHT11PIN);

  String rainVal=Rain();
  int humVal=humidity();
  int tempval=temp();
  int airVal=airMQ2();
  Serial.println("______");
  delay(1500);
  
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

float humidity()
{
  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);
  return (float)DHT11.humidity;
}
float temp()
{
  
  Serial.print("Temperature  (C): ");
  Serial.println((float)DHT11.temperature, 2);
  return (float)DHT11.temperature;
}

int airMQ2()
{
  Serial.print("Analog MQ2 output: ");
  int MQ2val = readSensor();
  Serial.println(MQ2val);
  return MQ2val;
}
