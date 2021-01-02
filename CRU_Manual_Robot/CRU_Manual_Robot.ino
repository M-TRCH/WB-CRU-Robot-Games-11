#include "CRU_MotorControl.h"
#include "CRU_MovementControl.h"
// #include "CRU_GyroFlawless.h"
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
#define RESET_PIN 3          // reset switch take interrupt pin

void(*resetFunc)(void) = 0; /* reset all function */
void resetEvent() /* command when arduino reset */
{
  four_wheel_drive(0, 0, 0, 0);
}
void softReset() /* debounce switch , interrupt function */
{
  if(digitalRead(RESET_PIN) == LOW)
  {
    delayMicroseconds(500);
    if(digitalRead(RESET_PIN) == LOW)
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
  pinMode(RESET_PIN, INPUT_PULLUP);
  // while(digitalRead(3));
  
  delay(1000);
  attachInterrupt(digitalPinToInterrupt(RESET_PIN), softReset, CHANGE);
  //////////////////////////////////////
  Serial.println("robot status : started");  
}
/*---------------------------------------- HAND AND ARM ----------------------------------------*/
#ifdef _CRU_SERVOTINY_H_
uint8_t arm_number = 0;                              // number of arm (1-4)
float Deg_rotArm[5]  = {0, -570, -570, -570, -570};  // degree of each arm (MIN_SAFE-MAX_SAFE) 
float Deg_rotHand[5] = {0,   60,   60,   60,   60};  // degree of each hand (MIN_SAFE-MAX_SAFE) 
#define ARM_SPD 2                                    // dynamixel motor speed for arm
#define ARM_SPD_RESOLUTION  5.5                      // resolution of degree per times (arm)
#define HAND_SPD_RESOLUTION 3.8                      // resolution of degree per times (hand)
#define PRESS_DELAY 150                              // wait for unpress button  
boolean armEvent  = false,                           // condition for arm working
        handEvent = false,                           // condition for hand working
        armState  = true,                            // up and down swiching variable
        handState = true;                            // "---------------------------"
        
void joint_select() /* arm number selection */
{       
       if(press(KEY_1)){ arm_number = 1; }
  else if(press(KEY_2)){ arm_number = 2; }
  else if(press(KEY_3)){ arm_number = 3; }
  else if(press(KEY_4)){ arm_number = 4; }
}
void arm_control() /* arm control part */
{
  if(press(KEY_F10)) 
  { /* lift up the robot arm */
    Deg_rotArm[arm_number] += ARM_SPD_RESOLUTION; 
    Deg_rotArm[arm_number] = constrain(Deg_rotArm[arm_number], JOINT_MIN_POS_SAFE, JOINT_MAX_POS_SAFE);
    armEvent = true;
  }
  else if(press(KEY_0))
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
    
    servoWrite(arm_number, int(Deg_rotHand[arm_number])); 
    handEvent = false;
  }
}
#endif
/*-------------------------------------- DRIVE MOVEMENT  ---------------------------------------*/
#ifdef _CRU_MOTORCONTROL_H_
#define Kp 25               // kp gain
#define NORMAL_SPD     1000 // forward and backward speed
#define NORMAL_DROP_SPD  50 // forward and backward drop speed
#define TURN_SPD        150 // turn right and turn left speed
#define TURN_DROP_SPD    50 // turn right and turn left drop speed
#define SLIDE_SPD       800 // slide right and slide left speed
#define SLIDE_DROP_SPD   50 // slide right and slide left drop speed
boolean dropState = false,  // condition for drop each speed
        moveEvent = false;  // condition for movement working
        
void drive_setting() /* movement setting */  
{
  if(press(KEY_OK))
  { /* speed speed */
    while(press(KEY_OK));
    dropState = !dropState;
  }
}
void drive_control() /* vector speed and heading control */
{
  float cps = 0; // -getYaw()*Kp;  // compensate value 
  uint16_t vector = 0, // robot vector value
           speed_ = 0; // robot speed value
  
  if(press(KEY_W))
  { /* turn rigth */
    cps = dropState ? TURN_DROP_SPD : TURN_SPD;
    moveEvent = true;
  }
  else if(press(KEY_Q))
  { /* turn left */
    cps = dropState ? -TURN_DROP_SPD : -TURN_SPD;
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
    drive(speed_, vector, cps);
    moveEvent = false;
  }
  else
  { /* stop */
    drive(0, 0, 0);
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
}


 
