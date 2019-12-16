///////////////////////////////////////////////////
//Serial communication protocol for Arduino Micro//
//Date: 12 November 2019                         //
//Author: Radu Chirila                           //
///////////////////////////////////////////////////

#define p 11
#define led 7 // onboard led?
int data;
void setup() 
{
  pinMode(p, OUTPUT);
  pinMode(led, OUTPUT);
  Serial1.begin(38400); 
  Serial1.write("AT+MODE=1\n");
  Serial1.write("AT+CMODE = 0\n");
  Serial1.write("AT+BIND = 0014,03,0600fe\n");
  Serial.begin(9600);
}

void loop() 
{
  analogWrite(p,1);
  digitalWrite(led,LOW);
  if(Serial1.available()>0)
  {
    data = Serial1.read();
    digitalWrite(led, HIGH);
  }
  Serial1.write(data);
  Serial.println("Transfer registered!");
  delay(10);
}
  
