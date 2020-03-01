
#define LED 13

int index=0;
uint8_t positions[14];
inline void transmit();

inline void receive()
{
  if(Serial1.available()>0)
  {
    
    uint8_t data = Serial1.read();
    Serial.print(data);
    Serial.print("  ");
    //delay(10);
    //data = map(data, 70 , 200, 0, 180);
    //thumb.write(data);
  }
  else{
    Serial.println("");
    return;
  }
  receive();
}
inline void transmit(int j)
{
  memset(positions,1,sizeof(positions));
  positions[j]=2;
  for(int i=0;i<14;++i)
  {
    Serial1.write((uint8_t)positions[i]);
    //Serial.print(positions[i]);
  }
  Serial.println("\n");
}
inline void send_pad()
{ 
  for(int i = 0; i<5;++i)
  {
    Serial1.write(0);
  }
}
inline void reset()
{
  memset(positions,1,sizeof(positions));
}
void setup()
{
  //thumb.attach(10); 
  Serial.begin(19200);
  Serial1.begin(19200);
}
void loop()
{
  send_pad();
  transmit(index);
  send_pad();
  receive();
  index++;
  if(index==13)
  {
    index = 0;
  }
}
