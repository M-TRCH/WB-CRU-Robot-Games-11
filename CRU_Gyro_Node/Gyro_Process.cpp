#include "Gyro_Process.h"
#include "MPU6050_6Axis_Motion.h"

#define OUTPUT_READABLE_YAWPITCHROLL

MPU6050 mpu;
Quaternion q; 
VectorInt16 aa; 
VectorInt16 aaReal; 
VectorInt16 aaWorld; 
VectorFloat gravity; 

gyro::gyro()
{
}
gyro::~gyro()
{
}
void gyro::setOffset(int16_t set_aZ, int16_t set_gX, int16_t set_gY, int16_t set_gZ) /* offset value defined */
{
 offset_aZ = set_aZ;  
 offset_gX = set_gX; 
 offset_gY = set_gY;
 offset_gZ = set_gZ;
}
void gyro::initial() /* gyro (mpu6050)initialize  */
{
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    Wire.begin();
    TWBR = 24; 
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
    Fastwire::setup(400, true);
  #endif

 mpu.initialize();
 devStatus = mpu.dmpInitialize();

 mpu.setXGyroOffset(offset_gX);
 mpu.setYGyroOffset(offset_gY);
 mpu.setZGyroOffset(offset_gZ);
 mpu.setZAccelOffset(offset_aZ); 
 
 if (devStatus == 0) 
 {
  mpu.setDMPEnabled(true);
  mpuIntStatus = mpu.getIntStatus();
  dmpReady = true;
  packetSize = mpu.dmpGetFIFOPacketSize();
 }  
}
void gyro::setSetpoint() /* setpoing value setting */
{
  getVal(); setpoint = yaw;
}
void gyro::prepare(unsigned long interval_timeCheck, unsigned long timeout) /* waiting for yaw value to stable */
{
 unsigned long start_time = 0;
 unsigned long start_loop_time = millis();
 
 while(true)
 {
  start_time = millis();
  while((millis()-start_time) < interval_timeCheck){ getVal(); first_yaw = yaw;  }
  start_time = millis();
  while((millis()-start_time) < interval_timeCheck){ getVal(); second_yaw = yaw; }
 
       if(int(first_yaw) == int(second_yaw))  { break; }
  else if(millis()-start_loop_time > timeout) { break; } 
 }
 setSetpoint();
}
float gyro::getVal(bool getProcess_value) /* get yaw value */
{
 if(!dmpReady) return;
 while (!mpuInterrupt && fifoCount < packetSize){ }

 mpuInterrupt = false;
 mpuIntStatus = mpu.getIntStatus();
 fifoCount    = mpu.getFIFOCount();

      if((mpuIntStatus & 0x10) || fifoCount == 1024){ mpu.resetFIFO(); } 
 else if (mpuIntStatus & 0x02) 
 {
  while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
  mpu.getFIFOBytes(fifoBuffer, packetSize);
  fifoCount -= packetSize;
  #ifdef OUTPUT_READABLE_YAWPITCHROLL
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
    yaw   = ypr[0]*(180/M_PI);
    pitch = ypr[1]*(180/M_PI); 
    row   = ypr[2]*(180/M_PI);
  #endif
 }
 
 if(yaw < 0) yaw = 360+yaw; // the value convert is 0-360
 if(getProcess_value == true)
 { /* setpoint calucation */
  if(setpoint >= 0 && setpoint <= 180)
  {
   if(yaw > setpoint+180) yaw = yaw-360;
  }
  else 
  {
   if(yaw < setpoint-180) yaw = 360+yaw;
  }
  yaw = setpoint-yaw;
 }
 return yaw;
}
float gyro::getVal() /* runing get yaw process but don't get yaw value */
{
  getVal(false);
}
