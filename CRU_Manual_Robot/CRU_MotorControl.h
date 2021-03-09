#include "Dynamixel_for_Arduino.h"
#define _CRU_MOTORCONTROL_H_ 
/*-------------------------------------- parameter setting --------------------------------------*/
/* communication */
SoftwareSerial DX_SERIAL(7, 8);
#define DX_SERIAL_BAUD   57142
/* object define */
DX FR_drive;
DX FL_drive;
DX BR_drive;
DX BL_drive;
DX RR_joint;
DX RM_joint;
DX LM_joint;
DX LL_joint;
/* motor ID */
#define FR_DRIVE_ID 2
#define FL_DRIVE_ID 3
#define BR_DRIVE_ID 1
#define BL_DRIVE_ID 4
#define RR_JOINT_ID 99   
#define RM_JOINT_ID 11   
#define LM_JOINT_ID 12
#define LL_JOINT_ID 14
/* wheel mode parameter */
#define DRIVE_SPD_RANGE 1000
/* joint mode parameter */
#define JOINT_SPD_RANGE 10
#define JOINT_MAX_POS_RANGE  600
#define JOINT_MIN_POS_RANGE -600
#define JOINT_MAX_POS_SAFE  -365 // arm down
#define JOINT_MIN_POS_SAFE  -540 // arm up
/*-----------------------------------------------------------------------------------------------*/
                                         
void dynamixel_init() /* dymanixel motor initial (include setSpeed setSafeDeg setMode .. ) */
{
/*-------------------------------------- wheel mode initial -------------------------------------*/
  FR_drive.begin(&DX_SERIAL, DX_SERIAL_BAUD);
  FR_drive.setMode("WHEEL");
  FR_drive.setID(FR_DRIVE_ID);
  FR_drive.setSpeedRange(-DRIVE_SPD_RANGE, DRIVE_SPD_RANGE);
  
  FL_drive.begin(&DX_SERIAL, DX_SERIAL_BAUD);
  FL_drive.setMode("WHEEL");
  FL_drive.setID(FL_DRIVE_ID);
  FL_drive.setSpeedRange(-DRIVE_SPD_RANGE, DRIVE_SPD_RANGE);
  
  BR_drive.begin(&DX_SERIAL, DX_SERIAL_BAUD);
  BR_drive.setMode("WHEEL");
  BR_drive.setID(BR_DRIVE_ID);
  BR_drive.setSpeedRange(-DRIVE_SPD_RANGE, DRIVE_SPD_RANGE);
  
  BL_drive.begin(&DX_SERIAL, DX_SERIAL_BAUD);
  BL_drive.setMode("WHEEL");
  BL_drive.setID(BL_DRIVE_ID);
  BL_drive.setSpeedRange(-DRIVE_SPD_RANGE, DRIVE_SPD_RANGE);

/*-------------------------------------- joint mode initial -------------------------------------*/
  LL_joint.begin(&DX_SERIAL, DX_SERIAL_BAUD);
  LL_joint.setMode("JOINT");
  LL_joint.setID(LL_JOINT_ID);
  LL_joint.setSpeedMax(JOINT_SPD_RANGE);
  LL_joint.setPosRange(JOINT_MIN_POS_RANGE, JOINT_MAX_POS_RANGE);
  LL_joint.setPosLimit(JOINT_MIN_POS_SAFE, JOINT_MAX_POS_SAFE);

  LM_joint.begin(&DX_SERIAL, DX_SERIAL_BAUD);
  LM_joint.setMode("JOINT");
  LM_joint.setID(LM_JOINT_ID);
  LM_joint.setSpeedMax(JOINT_SPD_RANGE);
  LM_joint.setPosRange(JOINT_MIN_POS_RANGE, JOINT_MAX_POS_RANGE);
  LM_joint.setPosLimit(JOINT_MIN_POS_SAFE, JOINT_MAX_POS_SAFE);

  RM_joint.begin(&DX_SERIAL, DX_SERIAL_BAUD);
  RM_joint.setMode("JOINT");
  RM_joint.setID(RM_JOINT_ID);
  RM_joint.setSpeedMax(JOINT_SPD_RANGE);
  RM_joint.setPosRange(JOINT_MIN_POS_RANGE, JOINT_MAX_POS_RANGE);
  RM_joint.setPosLimit(JOINT_MIN_POS_SAFE, JOINT_MAX_POS_SAFE);

  RR_joint.begin(&DX_SERIAL, DX_SERIAL_BAUD);
  RR_joint.setMode("JOINT");
  RR_joint.setID(RR_JOINT_ID);
  RR_joint.setSpeedMax(JOINT_SPD_RANGE);
  RR_joint.setPosRange(JOINT_MIN_POS_RANGE, JOINT_MAX_POS_RANGE);
  RR_joint.setPosLimit(JOINT_MIN_POS_SAFE, JOINT_MAX_POS_SAFE);
}
void four_wheel_drive(int16_t FL_spd, int16_t FR_spd, int16_t BL_spd, int16_t BR_spd) /* four wheel mecanum drive */
{
  FL_drive.rotate(FL_spd);
  FR_drive.rotate(FR_spd);
  BL_drive.rotate(BL_spd);
  BR_drive.rotate(BR_spd);
}
