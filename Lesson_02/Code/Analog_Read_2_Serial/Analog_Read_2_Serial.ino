


int AnalogPin = 0;
int DelayTime = 10; // 10 milliseconds


void setup() 
{
  Serial.begin(9600);     // init. serial com. at 9600 bits per sec.
}

void loop() 
{
  int sensorValue = analogRead(AnalogPin);   // read analog: 0 to 1023 (10 bits)
  
  Serial.println(sensorValue);   // print out the value you read
  delay(DelayTime);                
}


