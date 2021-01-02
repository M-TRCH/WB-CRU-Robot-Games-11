#include "Holonomic_Equation.h"
#define _CRU_MOVEMENTCONTROL_H_
/*-------------------------------------- parameter setting --------------------------------------*/
/* holonomic movement */
holonomic mecanum;
#define NUMBER_WHEEL 4
/*-----------------------------------------------------------------------------------------------*/

void holonomic_init() /* holonomic movement initial */
{
  mecanum.setWheel(NUMBER_WHEEL);
}
void drive(uint16_t velocity, uint16_t theta, int16_t omega) /* movement control for easy use */
{
  mecanum.GetfourwheelSPD(velocity, theta, omega);
  four_wheel_drive(mecanum.GetSpd(0), mecanum.GetSpd(1), mecanum.GetSpd(2), mecanum.GetSpd(3));
}
