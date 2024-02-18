#define rainPin A1
void setup() 
{
    Serial.begin(9200);
    pinMode(rainPin,INPUT); 
    
}

void loop() 
{
  int rainData=analogRead(rainPin);
  // if rain detects rainData is 0 else rainData is 1
  Serial.println(rainData);
  delay(1000);
}
