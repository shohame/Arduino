int LedPin = 8;
int AnalogPin = 0;
int LedValue = HIGH;

void setup() 
{
Serial.begin(9600);    
pinMode(LedPin, OUTPUT);
}

void loop() 
{
int sensorValue = analogRead(AnalogPin);   
   
    Serial.println(sensorValue );  

    digitalWrite(LedPin, LedValue);
  
    delay(sensorValue);       
 
  if (LedValue  ==  HIGH)
  {
   LedValue  =  LOW;
  }
  else
  {
     LedValue  =  HIGH;
  }
}

