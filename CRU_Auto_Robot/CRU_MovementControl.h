#include "Holonomic_Equation.h"
#define _CRU_MOVEMENTCONTROL_H_
/*-------------------------------------- parameter setting --------------------------------------*/
/* holonomic movement */
holonomic Omni;
#define NUMBER_WHEEL 3
/*-----------------------------------------------------------------------------------------------*/

void holonomic_init() /* holonomic movement initial */
{
  Omni.setWheel(NUMBER_WHEEL);
}
void drive(uint16_t velocity, uint16_t theta, int16_t omega) /* movement control for easy use */
{
  Omni.GetthreewheelSPD(velocity, theta, omega);
  wheel_drive(Omni.GetSpd(0), Omni.GetSpd(1), Omni.GetSpd(2));
}
