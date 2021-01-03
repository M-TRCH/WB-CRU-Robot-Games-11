#include "CRU_MotorControl.h"
#include "CRU_MovementControl.h"

#include <Pixy2.h>
Pixy2 pixy;
//----------------Gyro----------------//
#include <I2Cdev.h>
#include <MPU6050_6Axis_MotionApps20.h>
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include <Wire.h>
#endif

MPU6050 mpu;

#define OUTPUT_READABLE_YAWPITCHROLL
bool dmpReady = false;
uint8_t  mpuIntStatus;
uint8_t  devStatus;
uint16_t packetSize;
uint16_t fifoCount;
uint8_t  fifoBuffer[64];
int senderror ;
Quaternion q;         // [w, x, y, z] quaternion container
VectorInt16 aa;       // [x, y, z] accel sensor measurements
VectorInt16 aaReal;   // [x, y, z] gravity-free accel sensor measurements
VectorInt16 aaWorld;  // [x, y, z] world-frame accel sensor measurements
VectorFloat gravity;  // [x, y, z] gravity vector
float euler[3];       // [psi, theta, phi] Euler angle container
float ypr[3];         // [yaw, pitch, roll] yaw/pitch/roll container and gravity vector

uint8_t teapotPacket[14] = { '$', 0x02, 0, 0, 0, 0, 0, 0, 0, 0, 0x00, 0x00, '\r', '\n' };
volatile bool mpuInterrupt = false;
void dmpDataReady() {
  mpuInterrupt = true;
}

float degree, Setpoint, Error;
double P, D, I, pid, P_error = 0 ;

double Kp = 2.3f ; //2.5
double Ki = 0.0f ; //0.0
double Kd = 0.4f ; //1.0
/*-------------------------------------------------------------------------------------------------*/
void setup() 
{
  Serial.begin(9600);

  dynamixel_init();
  holonomic_init();

    //----------------Gyro----------------//
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
  TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif
  devStatus = mpu.dmpInitialize();

  // supply your own gyro offsets here, scaled for min sensitivity
  mpu.setXGyroOffset(49);  //49
  mpu.setYGyroOffset(-79);   //-79
  mpu.setZGyroOffset(-11);  //-11
  mpu.setZAccelOffset(5619); // 1688 factory default for my test chip

  if (devStatus == 0) {
    mpu.setDMPEnabled(true);

    attachInterrupt(0, dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();

    dmpReady = true;

    packetSize = mpu.dmpGetFIFOPacketSize();
  }
  else {}
  
  pixy.init();
  Rotate_joint.rotate(2, -405); //C
  Gyro_set();
  pixy.setLamp(1, 1);

  Set_Heading(0,   500);
  Set_Heading(-60, 4000);
  Set_Heading(60,  4000);
  Set_Heading(90,  2000);
  Oblique_F(2500);
}

void loop() 
{  
  //--1--//
  Tracking();
  drive(150, 90, 0); delay(500);  drive(0, 0, 0);  delay(500);
  drive(150, 270, 0);delay(500);  drive(0, 0, 0);  delay(500);
  drive(150, 0, 40); delay(2400); drive(0, 0, 0);  delay(500);
  //--2--//
  Tracking();
  drive(150, 90, 0); delay(500);  drive(0, 0, 0);  delay(500);
  Rotate_joint.rotate(2, -465); //L
  delay(2000);
  Rotate_joint.rotate(2, -585); //CC
  delay(2000);
  Rotate_joint.rotate(2, -405); //C
  drive(150, 270, 0);delay(500);  drive(0, 0, 0);  delay(500);
  drive(150, 0, 40); delay(4700); drive(0, 0, 0);  delay(500);
  //--3--//
  Tracking();
  drive(150, 90, 0);    delay(500);  drive(0, 0, 0);  delay(500);
  Rotate_joint.rotate(2, -345); //R
  delay(2000);
  Rotate_joint.rotate(2, -585); //CC
  delay(2000);
  Rotate_joint.rotate(2, -405); //C
  drive(150, 270, 0);   delay(500);  drive(0, 0, 0);  delay(500);
  drive(150, 180, -40); delay(2400); drive(0, 0, 0);  delay(500);
  //--4--//
  Tracking();
  drive(150, 90, 0);    delay(500);  drive(0, 0, 0);  delay(500);
  drive(150, 270, 0);   delay(500);  drive(0, 0, 0);  delay(500);
  Oblique_B(2500);
  while(1);
}


//  Rotate_joint.rotate(2, -585); //CC
//  Rotate_joint.rotate(2, -405); //C
//  Rotate_joint.rotate(2, -465); //L
//  Rotate_joint.rotate(2, -345); //R
