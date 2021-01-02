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
void holonomic::GetfourwheelSPD(float velocity, float heading, float omega) /* four wheel mecanum and omni movement equation */
{
  if(no_wheel == 4)
  {
    heading *= degTorad;
    const float cos_theta = cos(heading);
    const float sin_theta = sin(heading);
    
    first_spd  = (velocity * (cos_theta*-root2divide2 + sin_theta*-root2divide2)) - omega;
    second_spd = (velocity * (cos_theta*-root2divide2 + sin_theta* root2divide2)) - omega;
    third_spd  = (velocity * (cos_theta* root2divide2 + sin_theta* root2divide2)) - omega;
    fourth_spd = (velocity * (cos_theta* root2divide2 + sin_theta*-root2divide2)) - omega;
  }
}
float holonomic::GetSpd(uint8_t no) /* get the speed of each wheel */
{
  float spd = 0.000f;
       if(no == 0) spd = first_spd;
  else if(no == 1) spd = second_spd;
  else if(no == 2) spd = third_spd;
  else if(no == 3) spd = fourth_spd;
  // Serial.println(spd); // {SERIAL_ACTIVED}
  return spd; 
}
