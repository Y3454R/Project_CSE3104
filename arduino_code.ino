#include<Servo.h>

//soil moisture
int WET= 3; 
int DRY= 2;  
int Sensor= 0; // Soil Sensor input at Analog PIN A0
int value= 0;

// temp
int val;
int tempPin = 1;
#define cold_R 8
#define optimum_Y 6
#define warm_G 5
#define fire_B 4

// Servo
Servo Myservo;
int pos;

void setup()
{
  Serial.begin(9600);
  // temp
  pinMode(cold_R,OUTPUT);
  pinMode(optimum_Y,OUTPUT);
  pinMode(warm_G,OUTPUT);
  pinMode(fire_B,OUTPUT);
  // soil
  pinMode(WET, OUTPUT);
  pinMode(DRY, OUTPUT);
  // servo
  Myservo.attach(9);
  
}
void loop()
{
  val = analogRead(tempPin);
  float mv = ( val/1024.0)*5000;
  float cel = mv/40;
  float temp = (cel*9)/5 + 32;
  //Serial.print("TEMPRATURE = ");
  Serial.print(temp);
  Serial.print(",");
  //Serial.print("*F"); 
  //Serial.println();
  if(temp<=80) 
  {
    digitalWrite(optimum_Y,LOW);
    digitalWrite(warm_G,LOW);
    digitalWrite(fire_B,LOW);
    digitalWrite(cold_R,HIGH);
  }
  else if(temp<=85)
  {
    digitalWrite(cold_R,LOW);
    digitalWrite(warm_G,LOW);
    digitalWrite(fire_B,LOW);
    digitalWrite(optimum_Y,HIGH);
  }
  else if(temp<=135)
  {
    digitalWrite(cold_R,LOW);
    digitalWrite(optimum_Y,LOW);
    digitalWrite(fire_B,LOW);
    digitalWrite(warm_G,HIGH);
  }
  else 
  {
    digitalWrite(cold_R,LOW);
    digitalWrite(optimum_Y,LOW);
    digitalWrite(warm_G,LOW);
    digitalWrite(fire_B,HIGH);
  }
  ////////////////
  value= analogRead(Sensor);
  value= value/10 * 8;
  Serial.println((float)value);
  if(value<50){
     // digitalWrite(WET, HIGH);
     ///////////
     // servo
     for(pos=0;pos<=180;pos++){
        Myservo.write(pos);
        delay(15);
     }
     delay(1000);
  
    for(pos=180;pos>=0;pos--){
      Myservo.write(pos);
      delay(15);
    }
    delay(1000);
    // servo ends
    
   }
   else
   {
      //digitalWrite(DRY,HIGH);
   }
   digitalWrite(WET,LOW);
   digitalWrite(DRY, LOW);
   //////////////////
  delay(5000);

}