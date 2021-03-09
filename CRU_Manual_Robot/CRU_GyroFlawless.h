#define _CRU_GYROFLAWLESS_H_
/*-------------------------------------- parameter setting --------------------------------------*/
/* gyro parameter setting */
#define INPUT_PIN 5         // input data pin
#define PULSE_TIMEOUT 8000  // pulse in checking timeout
#define PULSE_IN_MAX  1991  // pulse in max value
#define PULSE_IN_MIN    24  // pulse in min value
#define YAW_OUT_MAX    180  // yaw output max value 
#define YAW_OUT_MIN   -180  // yaw output min value
/*-----------------------------------------------------------------------------------------------*/

void gyro_init() /* gyro define parameter and running initialize precess */
{
  delay(100);
}
float getYaw() /* get yaw value (process value) */
{
  uint16_t rawYaw = pulseIn(INPUT_PIN, HIGH, PULSE_TIMEOUT);
  int16_t outYaw = map(rawYaw, PULSE_IN_MIN, PULSE_IN_MAX, YAW_OUT_MIN, YAW_OUT_MAX);
   Serial.print(rawYaw); // {SERIAL_ACTIVED}
   Serial.print("\t");
  return outYaw;
}
