#define analogPin      A0          // analog pin for measuring capacitor voltage
#define chargePin      23         // pin to charge the capacitor - connected to one end of the charging resistor
#define dischargePin   22         // pin to discharge the capacitor

unsigned long startTime;
unsigned long elapsedTime;
float capacitance;

void setup(){
  pinMode(chargePin, OUTPUT);     
  digitalWrite(chargePin, LOW);  
  pinMode(dischargePin, INPUT);
  Serial.begin(9600); 
}

inline void charge(void)
{
  
  int t1=micros();
  pinMode(chargePin,OUTPUT);
  pinMode(dischargePin, INPUT);

  int t2;
  do{
  digitalWrite(chargePin,HIGH);
  }while(analogRead(analogPin)<1020);

  
   pinMode(chargePin,INPUT);
  pinMode(dischargePin, OUTPUT);
  do{
    digitalWrite(dischargePin,LOW);
  }while(analogRead(analogPin)>0);
  t2=micros();
  if(t2-t1<29 && t2-t1>0)
  Serial.println(t2-t1);
  delay(1);
}

void loop(){
 charge();
}
