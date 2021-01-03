#include "Holonomic_Equation.h"

holonomic::holonomic()
{
  
}
holonomic::~holonomic()
{
  
}
void holonomic::setWheel(uint8_t num) /* set number of wheel */
{
  if(num > 0) no_wheel = num;
}
void holonomic::GetthreewheelSPD(float Sp, float Ceta, float Omega) /* four wheel mecanum and omni movement equation */
{
  if(no_wheel == 3)
  {
    float D2R = degTorad;
    const float Vx = Sp * cos(Ceta * D2R);
    const float Vy = Sp * sin(Ceta * D2R);
    
    first_spd  =   Vy * cos(30 * D2R) - Vx * sin(30 * D2R) + Omega;
    second_spd = - Vy * cos(30 * D2R) - Vx * sin(30 * D2R) + Omega;
    third_spd  =   Vx + Omega;
  }
}
float holonomic::GetSpd(uint8_t no) /* get the speed of each wheel */
{
  float spd = 0.000f;
       if(no == 0) spd = first_spd;
  else if(no == 1) spd = second_spd;
  else if(no == 2) spd = third_spd;
  // Serial.println(spd); // {SERIAL_ACTIVED}
  return spd; 
}
