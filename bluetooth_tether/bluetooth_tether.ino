#define LED 13
void setup()
{
  Serial.begin(19200);
  Serial1.begin(19200);
}

void loop()
{ 
  byte r;
  if(Serial1.available()>0)
  {
    Serial.println((int)Serial1.read());
  }
}
