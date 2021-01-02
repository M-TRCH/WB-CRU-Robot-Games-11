#include "Gyro_Process.h"
#define _CRU_GYROFLAWLESS_H_
/*-------------------------------------- parameter setting --------------------------------------*/
/* object define */
gyro gyro;
/* gyro parameter setting */
#define INTERRUPT_PIN digitalPinToInterrupt(2) // ineterrupt pin
#define gyroOffsetX 220    // gyro x offset
#define gyroOffsetY 76     // gyro y offset
#define gyroOffsetZ -85    // gyro z offset
#define accelOffsetZ 1788  // accel z offset
#define interval_timeCheck 2000  // interval time to prepare checking 
#define prepare_timeout    30000 // gyro preparing timeout value 
/*-----------------------------------------------------------------------------------------------*/

void interrupt_event() /* interrupt event of internal gyro library */
{
  gyro.mpuInterrupt = true;
}
void gyro_init() /* gyro define parameter and running initialize precess */
{
  attachInterrupt(INTERRUPT_PIN, interrupt_event, RISING);
  gyro.setOffset(accelOffsetZ, gyroOffsetX, gyroOffsetY, gyroOffsetZ);
  gyro.initial();  
  gyro.prepare(interval_timeCheck, prepare_timeout);
}
float getYaw() /* get yaw value (process value) */
{
  return gyro.getVal(true);
}
