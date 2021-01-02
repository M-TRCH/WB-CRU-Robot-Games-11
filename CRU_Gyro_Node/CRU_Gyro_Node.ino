#include "CRU_GyroFlawless.h"
#define output_pin 3

void setup()
{
  Serial.begin(9600);
  gyro_init();  
}
void loop() 
{
  float outYaw = map(getYaw(), -180, 180, 3, 252);
  analogWrite(output_pin, int(outYaw));
  Serial.println(int(outYaw));
}
