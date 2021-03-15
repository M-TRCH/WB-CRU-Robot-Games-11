#include "Dynamixel_for_Arduino.h"
#define _CRU_MOTORCONTROL_H_ 
/*-------------------------------------- parameter setting --------------------------------------*/
/* communication */
SoftwareSerial DX_SERIAL(9, 8);
#define DX_SERIAL_BAUD   57142
/* object define */
DX W1_drive;
DX W2_drive;
DX W3_drive;
DX Rotate_joint;
DX Kept_joint;
/* motor ID */
#define W1_DRIVE_ID     1
#define W2_DRIVE_ID     3
#define W3_DRIVE_ID     2
#define Rotate_JOINT_ID 4
#define Kept_JOINT_ID   5
/* wheel mode parameter */
#define DRIVE_SPD_RANGE 1000
/* joint mode parameter */
#define JOINT_SPD_RANGE 10
#define JOINT_MAX_POS_RANGE  600
#define JOINT_MIN_POS_RANGE -600
#define JOINT_MAX_POS_SAFE   500
#define JOINT_MIN_POS_SAFE   -1000
/*-----------------------------------------------------------------------------------------------*/

void dynamixel_init() /* dymanixel motor initial (include setSpeed setSafeDeg setMode .. ) */
{
/*-------------------------------------- wheel mode initial -------------------------------------*/
  W1_drive.begin(&DX_SERIAL, DX_SERIAL_BAUD);
  W1_drive.setMode("WHEEL");
  W1_drive.setID(W1_DRIVE_ID);
  W1_drive.setSpeedRange(-DRIVE_SPD_RANGE, DRIVE_SPD_RANGE);
  
  W2_drive.begin(&DX_SERIAL, DX_SERIAL_BAUD);
  W2_drive.setMode("WHEEL");
  W2_drive.setID(W2_DRIVE_ID);
  W2_drive.setSpeedRange(-DRIVE_SPD_RANGE, DRIVE_SPD_RANGE);
  
  W3_drive.begin(&DX_SERIAL, DX_SERIAL_BAUD);
  W3_drive.setMode("WHEEL");
  W3_drive.setID(W3_DRIVE_ID);
  W3_drive.setSpeedRange(-DRIVE_SPD_RANGE, DRIVE_SPD_RANGE);

/*-------------------------------------- joint mode initial -------------------------------------*/
  Rotate_joint.begin(&DX_SERIAL, DX_SERIAL_BAUD);
  Rotate_joint.setMode("JOINT");
  Rotate_joint.setID(Rotate_JOINT_ID);
  Rotate_joint.setSpeedMax(JOINT_SPD_RANGE);
  Rotate_joint.setPosRange(JOINT_MIN_POS_RANGE, JOINT_MAX_POS_RANGE);
  Rotate_joint.setPosLimit(JOINT_MIN_POS_SAFE, JOINT_MAX_POS_SAFE);

  Kept_joint.begin(&DX_SERIAL, DX_SERIAL_BAUD);
  Kept_joint.setMode("JOINT");
  Kept_joint.setID(Kept_JOINT_ID);
  Kept_joint.setSpeedMax(JOINT_SPD_RANGE);
  Kept_joint.setPosRange(JOINT_MIN_POS_RANGE, JOINT_MAX_POS_RANGE);
  Kept_joint.setPosLimit(JOINT_MIN_POS_SAFE, JOINT_MAX_POS_SAFE);
}
/*-----------------------------------------------------------------------------------------------*/
void wheel_drive(int16_t W1_spd, int16_t W2_spd, int16_t W3_spd) 
{
  W1_drive.rotate(W1_spd);
  W2_drive.rotate(W2_spd);
  W3_drive.rotate(W3_spd);
}
