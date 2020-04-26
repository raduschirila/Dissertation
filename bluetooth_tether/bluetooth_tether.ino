#include "Servo.h"
#define LED 13
Servo thumb,index, ring,middle,pinky;
uint8_t positions[14];
uint8_t bends[9]={0,1,2,3,4,5,0};
uint8_t bb[9] = {0,10,20,20,20,20,0};
int indexx=0;
int time1;
int time2;
bool decrease=false;
inline void transmit();

inline inline void receive()// interpred received data
{
  if(Serial1.available()>4)//if there are 5 bytes of new information received over bluetooth
  {
    
    Serial.print("Sensors: ");//label data on USB link
    for(int i = 0; i<=4; ++i)
    {
      bends[i] = Serial1.read();
      switch(i){
        case 0:
        bends[i] = map(bends[i],125 ,175,20,170);//convert to angles
        pinky.write(bends[i]);//update position of finger
        break;
        case 1:
        bends[i] = map(bends[i],120,175,20,170);
        ring.write(bends[i]);
        break;
        case 2:
        bends[i] = map(bends[i],125,190,20,170);
        middle.write(bends[i]);
        break;
        case 3:
        bends[i] = map(bends[i],120,145,20,170);
        index.write(bends[i]);
        break;
        case 4:
        bends[i] = map(bends[i],120,185,20,170);
        thumb.write(bends[i]);
        break;
      }
      Serial.print(bends[i]);
      Serial.print(" ");
    }
    Serial.println();
  }
}

inline void transmit(int j)
{
  Serial.print("Motors: ");
  positions[j]=2;
  for(int i=0;i<14;++i)
  {
    Serial1.write((uint8_t)positions[i]);//send dummy pressure data
    Serial.print(positions[i]);
  }
  Serial.println("");
}
inline void send_pad()
{ 
  for(int i = 0; i<3;++i)//stop flags
  {
    Serial1.write(0);
  }
}
inline void reset()//reset buffer arrays
{
  memset(positions,1,sizeof(positions));
  memset(bends, 0,sizeof(bends));
}

void setup()//initialization sequence
{
  bool sync_complete=false;
  index.attach(12);
  middle.attach(11);
  ring.attach(10);
  thumb.attach(9);
  pinky.attach(8);
  Serial.begin(19200);
  Serial1.begin(19200);
  time1 = millis();
}
void timed_ISR()
{
    reset();
  transmit(indexx);
  indexx++;
  if(indexx ==14)
  indexx = 0;
  
}
void loop()
{
  if(millis() - time1 >= 10000);// if structure controls the frequency of the dummy data for testing purposes
  {
    timed_ISR();
    time1=millis();
  }
    if(millis() - time2 >= 18000);
  {
    receive();// realistically execution will start here
    time2=millis();
  }
  
}
