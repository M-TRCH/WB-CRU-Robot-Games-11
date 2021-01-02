#include <Servo.h> // arduino official libary //
#include <Wire.h>  //                         //
#include <Adafruit_PWMServoDriver.h>  // source on github : https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library
#define _CRU_SERVOTINY_H_
/*-------------------------------------- parameter setting --------------------------------------*/
#define HAND_MAX_POS_SAFE 145 // max degree of hand
#define HAND_MIN_POS_SAFE 30  // min degree of hand
#define FREQ_DRIVE 50         // normal pwm frequency of servo control
#define ADDRESS 0x40          // address to 16ch servo drive board
#define MAX_PULSE 600         // factory default
#define MIN_PULSE 150         // factory default
/*-----------------------------------------------------------------------------------------------*/
Adafruit_PWMServoDriver servo = Adafruit_PWMServoDriver(ADDRESS);

void servo_init() /* servo initialize */
{
  servo.begin();
  servo.setPWMFreq(FREQ_DRIVE); 
}
void servoWrite(uint8_t no, uint8_t deg) /* write and safety servo function */ 
{
  deg = constrain(deg, HAND_MIN_POS_SAFE, HAND_MAX_POS_SAFE);

       if(no == 1) no = 0; //                                       //
  else if(no == 2) no = 3; // convert to according normal positions //
  else if(no == 3) no = 1; //                                       //
  else if(no == 4) no = 2; //                                       //
  uint16_t period = map(deg, 0, 180, MIN_PULSE, MAX_PULSE);
  servo.setPWM(no, 0, period); // in one cycle 
}


 
