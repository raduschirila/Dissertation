///////////////////////////////////////////////////
//Serial communication protocol for Arduino Micro//
//Date: 12 November 2019                         //
//Author: Radu Chirila                           //
///////////////////////////////////////////////////

uint8_t data;
void setup() 
{
  Serial1.begin(38400); 
  Serial.begin(9600);
}

void loop() 
{

  if(Serial1.available()>0)
  {
    data = Serial1.read();
  }
  //Serial.print("Received: ");
  Serial.println(data);
  //delay(10);
}
  
