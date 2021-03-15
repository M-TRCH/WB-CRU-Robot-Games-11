//----------------MoveControl----------------//
#include "CRU_MotorControl.h"
#include "CRU_MovementControl.h"
//----------------Pixy_V.2----------------//
#include <Pixy2.h>
Pixy2 pixy;
//----------------Servo----------------//
#define servo 9
//----------------Laser_Sensor----------------//
#include <Wire.h>
#include <VL53L0X.h>

#define Sensor_L 10
#define Sensor_R 11

VL53L0X sensor;
//----------------Select----------------//
#define Sw_Blue   A3
#define Sw_Yellow A2
#define Sw_Red    A1
#define Sw_Str    3

int B,Y, R;
/*-------------------------------------------------------------------------------------------------*/

void setup() 
{
  Serial.begin(9600);

  dynamixel_init();
  holonomic_init();

  pinMode(servo, OUTPUT);
  
  pinMode(Sensor_L, OUTPUT);
  pinMode(Sensor_R, OUTPUT);
  
  pinMode(Sw_Blue,   INPUT);
  pinMode(Sw_Yellow, INPUT);
  pinMode(Sw_Red,    INPUT);
  pinMode(Sw_Str,    INPUT_PULLUP);
  
  Wire.begin();
  sensor.setTimeout(500);
  
  digitalWrite(Sensor_L, LOW);
  digitalWrite(Sensor_R, LOW);
  digitalWrite(servo, LOW);

  Set(2000);
}

void loop() 
{
  Select();
  //--------------Camera_Feedback--------------//
       if(R == 1 && Y == 0 && B == 0) { while(1){ if(digitalRead(Sw_Str) == 0) { break; } } delay(1000); Red_Duo(); }
  else if(Y == 1 && R == 0 && B == 0) { while(1){ if(digitalRead(Sw_Str) == 0) { break; } } delay(1000); Green_Duo(); }
  else if(B == 1 && Y == 0 && R == 0) { while(1){ if(digitalRead(Sw_Str) == 0) { break; } } delay(1000); Blue_Duo(); }
  //--------------No_Feedback--------------//
  else if(R == 0 && Y == 1 && B == 1) { while(1){ if(digitalRead(Sw_Str) == 0) { break; } } delay(1000); Red(); }
  else if(Y == 0 && R == 1 && B == 1) { while(1){ if(digitalRead(Sw_Str) == 0) { break; } } delay(1000); Green(); }
  else if(B == 0 && Y == 1 && R == 1) { while(1){ if(digitalRead(Sw_Str) == 0) { break; } } delay(1000); Blue(); }
  else if(R == 1 && Y == 1 && B == 1) { while(1){ if(digitalRead(Sw_Str) == 0) { break; } } delay(1000); Gray(); }
  else { while(1){ if(digitalRead(Sw_Str) == 0) { break; } } delay(1000); Last(); }


////--------------No_Feedback--------------//
//       if(R == 1 && Y == 0 && B == 0) { while(1){ if(digitalRead(Sw_Str) == 0) { break; } } delay(1000); Red_Duo_No(); }
//  else if(Y == 1 && R == 0 && B == 0) { while(1){ if(digitalRead(Sw_Str) == 0) { break; } } delay(1000); Green_Duo_No(); }
//  else if(B == 1 && Y == 0 && R == 0) { while(1){ if(digitalRead(Sw_Str) == 0) { break; } } delay(1000); Blue_Duo_No(); }
//  //--------------No_Feedback--------------//
//  else if(R == 0 && Y == 1 && B == 1) { while(1){ if(digitalRead(Sw_Str) == 0) { break; } } delay(1000); Red_No(); }
//  else if(Y == 0 && R == 1 && B == 1) { while(1){ if(digitalRead(Sw_Str) == 0) { break; } } delay(1000); Green_No(); }
//  else if(B == 0 && Y == 1 && R == 1) { while(1){ if(digitalRead(Sw_Str) == 0) { break; } } delay(1000); Blue_No(); }
//  else if(R == 1 && Y == 1 && B == 1) { while(1){ if(digitalRead(Sw_Str) == 0) { break; } } delay(1000); Gray_No(); }
}

void Select()
{
  if(analogRead(Sw_Blue) == 0) { B = 1; }
  else { B = 0; }

  if(analogRead(Sw_Yellow) == 0) { Y = 1; }
  else { Y = 0; }

  if(analogRead(Sw_Red) == 0) { R = 1; }
  else { R = 0; }
}
