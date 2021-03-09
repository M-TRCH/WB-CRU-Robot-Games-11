#include "CRU_MotorControl.h"
#include "CRU_MovementControl.h"
#include "CRU_GyroFlawless.h"
#include "CRU_JoyReader.h"
#include "CRU_ServoTiny.h"

/* "{SERIAL_ACTIVED}" <<< find keywords to check the print */
 
/* that library must be installed  
  >>> https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library
  >>> https://github.com/felis/USB_Host_Shield_2.0
*/

/*------------------------------------------- SYSTEM -------------------------------------------*/
#define HARDSERIAL_BAUD 9600 // default monitor baudrate
#define DEBUG_MODE           // debug mode enable
#define RSW_PIN 2            // rigth switch take enter pin
#define LSW_PIN 3            // left switch take interrupt pin

void(*resetFunc)(void) = 0; /* reset all function */
void resetEvent() /* command when arduino reset */
{
  four_wheel_drive(0, 0, 0, 0);
}
void softReset() /* debounce switch , interrupt function */
{
  if(digitalRead(RSW_PIN) == LOW)
  {
    delayMicroseconds(500);
    if(digitalRead(RSW_PIN) == LOW)
    {
      resetEvent();
      resetFunc();  
    }
  }
}
void system_init()
{
  #ifdef DEBUG_MODE
    Serial.begin(HARDSERIAL_BAUD);
    // while(!Serial);
  #endif
    
  delay(1000);  
  Serial.println("robot status : prepairing");  
  ///////////////////////////////////////
  pinMode(RSW_PIN, INPUT);
  pinMode(LSW_PIN, INPUT);
  // while(digitalRead(3));
  
  delay(1000);
  // attachInterrupt(digitalPinToInterrupt(RESET_PIN), softReset, CHANGE);
  //////////////////////////////////////
  Serial.println("robot status : started");  
}
/*---------------------------------------- HAND AND ARM ----------------------------------------*/
#ifdef _CRU_SERVOTINY_H_
uint8_t arm_number = 0;                              // number of arm (1-4)
float Deg_rotArm[5]  = {0, -570, -570, -570, -570};  // degree of each arm (MIN_SAFE-MAX_SAFE) 
float Deg_rotHand[5] = {0,   20,   20,   20,   20};  // degree of each hand (MIN_SAFE-MAX_SAFE) 
#define ARM_SPD 2                                    // dynamixel motor speed for arm
#define ARM_SPD_RESOLUTION  1.3                      // resolution of degree per times (arm)
#define HAND_SPD_RESOLUTION 3.8                      // resolution of degree per times (hand)
#define PRESS_DELAY 150                              // wait for unpress button  
boolean armEvent  = false,                           // condition for arm working
        handEvent = false,                           // condition for hand working
        armState  = true,                            // up and down swiching variable
        handState = true,                            // "---------------------------"
        safetyEvent = false;                         // special event for hand degree safety
#define Add_Deg_safetyHand 20                        // sum value of referent degree "(min+max)/2)" with me 
int16_t Deg_safetyHand = ((JOINT_MIN_POS_SAFE+JOINT_MAX_POS_SAFE)/2)-Add_Deg_safetyHand; // middle position of arm
        
void joint_select() /* arm number selection */
{       
       if(press(KEY_1)){ arm_number = 1; }
  else if(press(KEY_2)){ arm_number = 2; }
  else if(press(KEY_3)){ arm_number = 3; }
  else if(press(KEY_4)){ arm_number = 4; }
}
void arm_control() /* arm control part */
{
  if(press(KEY_TAP)) 
  { /* lift up the robot arm */
    Deg_rotArm[arm_number] += ARM_SPD_RESOLUTION; 
    Deg_rotArm[arm_number] = constrain(Deg_rotArm[arm_number], JOINT_MIN_POS_SAFE, JOINT_MAX_POS_SAFE);
    armEvent = true;
  }
  else if(press(KEY_CAPS))
  { /* lift down the robot arm */
    Deg_rotArm[arm_number] -= ARM_SPD_RESOLUTION; 
    Deg_rotArm[arm_number] = constrain(Deg_rotArm[arm_number], JOINT_MIN_POS_SAFE, JOINT_MAX_POS_SAFE);
    armEvent = true;
  } 
  else if(press(KEY_F1))
  { /* hotkey function to set max lift up and down */
    while(press(KEY_F1));
    // delay(PRESS_DELAY);
    if(armState) Deg_rotArm[arm_number] = JOINT_MAX_POS_SAFE;
    else         Deg_rotArm[arm_number] = JOINT_MIN_POS_SAFE;
    armEvent = true;
    armState = !armState; // switth lift up to lift down and lift down to lift up
  }
  else if(press(KEY_F3))
  { /* hotkey function to set max lift up and down */
    while(press(KEY_F3));
    // delay(PRESS_DELAY);
    
    Deg_rotArm[arm_number] = JOINT_MIN_POS_SAFE;
    armEvent = true;
  }
  if(armEvent)
  { /* activated when command */
//    Serial.print("ARM[");
//    Serial.print(arm_number);
//    Serial.print("]: ");
//    Serial.println(Deg_rotArm[arm_number]); // {SERIAL_ACTIVED}
      
         if(arm_number == 1){ LL_joint.rotate(ARM_SPD, int(Deg_rotArm[arm_number])); }
    else if(arm_number == 2){ LM_joint.rotate(ARM_SPD, int(Deg_rotArm[arm_number])); }
    else if(arm_number == 3){ RM_joint.rotate(ARM_SPD, int(Deg_rotArm[arm_number])); }
    else if(arm_number == 4){ RR_joint.rotate(ARM_SPD, int(Deg_rotArm[arm_number])); }
    armEvent = false;

    /* safety event when arm go to home */
    if(int(Deg_rotArm[arm_number]) < Deg_safetyHand) 
    {
      Deg_rotHand[arm_number] = HAND_MIN_POS_SAFE;
      handEvent = true;
      safetyEvent = true;
    }
  }
}
void hand_control() /* hand control part */
{
  if(press(KEY_WORM))
  { /* lift up the robot hand */
    Deg_rotHand[arm_number] += HAND_SPD_RESOLUTION; 
    Deg_rotHand[arm_number] = constrain(Deg_rotHand[arm_number], HAND_MIN_POS_SAFE, HAND_MAX_POS_SAFE);
    handEvent = true;
  }
  else if(press(KEY_ESC))
  { /* lift up the robot hand */
    Deg_rotHand[arm_number] -= HAND_SPD_RESOLUTION; 
    Deg_rotHand[arm_number] = constrain(Deg_rotHand[arm_number], HAND_MIN_POS_SAFE, HAND_MAX_POS_SAFE);
    handEvent = true;
  } 
  else if(press(KEY_F2))
  {  /* hotkey function to set max lift up */
    while(press(KEY_F2));
    // delay(PRESS_DELAY);
    
    if(handState) Deg_rotHand[arm_number] = HAND_MIN_POS_SAFE;
    else          Deg_rotHand[arm_number] = HAND_MAX_POS_SAFE; 
    handEvent = true;
    handState = !handState; 
  }
  if(handEvent)
  { /* activated when command */
//    Serial.print("HAND[");
//    Serial.print(arm_number);
//    Serial.print("]: ");
//    Serial.println(Deg_rotHand[arm_number]); // {SERIAL_ACTIVED}
    
    if(int(Deg_rotArm[arm_number]) > Deg_safetyHand || safetyEvent) 
    { // command denied while hand at home 
      servoWrite(arm_number, int(Deg_rotHand[arm_number]));
      safetyEvent = false;
    }
    handEvent = false;
  }
}
#endif
/*-------------------------------------- DRIVE MOVEMENT  ---------------------------------------*/
#ifdef _CRU_MOTORCONTROL_H_
#define Kp 12               // kp gain
#define NORMAL_SPD      800 // forward and backward speed
#define NORMAL_DROP_SPD  50 // forward and backward drop speed
#define TURN_CURVE_SPD  500 // turn right and turn left while curve move
#define TURN_SPD        100 // turn right and turn left speed
#define TURN_DROP_SPD    50 // turn right and turn left while drop speed
#define SLIDE_SPD       500 // slide right and slide left speed
#define SLIDE_DROP_SPD   50 // slide right and slide left drop speed
boolean dropState = false,  // condition for drop each speed
        moveEvent = false,  // condition for movement working
        closeLoop = false;  // close loop movement mode 
        
void drive_setting() /* movement setting */  
{
  if(press(KEY_OK))
  { /* speed speed */
    while(press(KEY_OK));
    dropState = !dropState;
  }
  if(press(KEY_SPACE))
  { /* speed speed */
    while(press(KEY_SPACE));
    closeLoop = !closeLoop;
  }
}
void drive_control() /* vector speed and heading control */
{
  float cps = closeLoop ? -getYaw()*Kp : 0; // compensate value 
  // Serial.println(cps); // {SERIAL_ACTIVED}
  uint16_t vector = 0, // robot vector value
           speed_ = 0; // robot speed value
  
  if(press(KEY_W))
  { /* turn rigth */
    cps = dropState ? TURN_DROP_SPD : TURN_CURVE_SPD;
    moveEvent = true;
  }
  else if(press(KEY_Q))
  { /* turn left */
    cps = dropState ? -TURN_DROP_SPD : -TURN_CURVE_SPD;
    moveEvent = true;
  }
///////////////////////////////////////////////////////
  if(press(KEY_UP))
  { /* forward */
    speed_ = dropState ? NORMAL_DROP_SPD : NORMAL_SPD;
    vector = 90;
    moveEvent = true;
  }
  else if(press(KEY_DOWN))
  { /* backward */
    speed_ = dropState ? NORMAL_DROP_SPD : NORMAL_SPD;
    vector = 270;
    moveEvent = true;
  }
  else if(press(KEY_RIGTH))
  { /* slide rigth */
    speed_ = dropState ? SLIDE_DROP_SPD : SLIDE_SPD;
    vector = 0;
    moveEvent = true;
  }
  else if(press(KEY_LEFT))
  { /* slide left */
    speed_ = dropState ? SLIDE_DROP_SPD : SLIDE_SPD;
    vector = 180;
    moveEvent = true;
  }
///////////////////////////////////////////////////////  
  if(moveEvent)
  {
    if(speed_ == 0 && abs(cps) != TURN_DROP_SPD)
    {// speed select when stop or run
           if(cps > 0) cps =  TURN_SPD;  
      else if(cps < 0) cps = -TURN_SPD;
    }
     
    drive(speed_, vector, cps);
    moveEvent = false;
//    Serial.print(speed_); //{SERIAL_ACTIVED}
//    Serial.print("\t");
//    Serial.print(vector);
//    Serial.print("\t");
//    Serial.println(cps);
  }
  else
  { /* stop */
    // cps = dropState ? TURN_DROP_SPD : TURN_SPD;
    drive(0, 0, cps);
  }
}
#endif
/*----------------------------------------------------------------------------------------------*/
void setup() 
{
  system_init();    // it about all the systems required
  dynamixel_init(); 
  holonomic_init(); 
  
 
  #ifdef _CRU_SERVOTINY_H_
    servo_init();
  #endif
  
  #ifdef _CRU_GYROFLAWLESS_H_
    gyro_init();
  #endif

  #ifdef _CRU_JOYREADER_H_
    usbJoy_init(); 
  #endif
}
void loop() 
{ 
  #ifdef _CRU_SERVOTINY_H_
    joint_select();
    arm_control();
    hand_control();
  #endif

  #ifdef _CRU_MOTORCONTROL_H_
    drive_setting();
    drive_control();
  #endif

//  FL_drive.rotate(100); delay(1000);
//  FR_drive.rotate(100); delay(1000);
//  BL_drive.rotate(100); delay(1000);
//  BR_drive.rotate(100); delay(1000);
  
// Serial.println(getYaw());
// getYaw();
// Serial.println(digitalRead(5));
// Serial.println(pulseIn(5, HIGH, 10000));
    
//       if(!digitalRead(RSW_PIN)) drive(80, 90 , 0);
//  else if(!digitalRead(LSW_PIN)) drive(80, 270, 0);
//  else drive(0, 0, 0);

}


 
