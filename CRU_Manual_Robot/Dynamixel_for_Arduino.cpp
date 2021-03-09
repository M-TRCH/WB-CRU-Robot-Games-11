#include "Dynamixel_for_Arduino.h"

DX::DX()
{

}
DX::~DX()
{

}
void DX::setMode(String mode) /* motor mode setting */
{
       if(mode == "JOINT") motor_mode = 1;
  else if(mode == "WHEEL") motor_mode = 2;
}
void DX::setID(uint8_t id)
{
  id_motor = id;
}
void DX::begin(SoftwareSerial *serial_arg,unsigned long baudrate) /* baudrate for communication setting */
{
  serial_arg -> begin(baudrate); // define bitperrate 
  serial_use = serial_arg;       // communication stream
}
/*---------------------------------------- for drive mode ---------------------------------------*/
void DX::setSpeedRange(int16_t spd_min, uint16_t spd_max) /* range speed drive setting */
{
  if(motor_mode == 2)
  {
    spd_minRange = spd_min; // min speed of speed mapping
    spd_maxRange = spd_max; // max speed of speed mapping
  }
}
void DX::rotate(int16_t spd) /* control motor rotation */
{
  if(motor_mode == 2)
  {
    uint16_t packet[6] = {0}, // communication data package 
             checksum = 0;    // summation checking data package 
  
    if(spd >= 0) 
    { /* limit highest range speed and data mapping */
      if(spd > spd_maxRange) spd = spd_maxRange; 
      spd = map(spd, 0, spd_maxRange, 1024, 2047); 
    }
    else
    { /* limit lowest range speed and data mapping */
      if(spd < spd_minRange) spd = spd_minRange;
      spd = map(spd, 0, spd_minRange, 0, 1023);
    }  
    packet[0] = id_motor;             // motor id
    packet[1] = 0x05;                 // lenght = instruction + 2
    packet[2] = 0x03;                 // writing type
    packet[3] = 0x20;                 // address of moving speed
    packet[4] = byte(spd);            // lowest byte speed
    packet[5] = byte((spd&0x700)>>8); // highest byte speed

    /* starting to data package transmission */
    serial_use->write(0xFF); delay(1); // header of the packet // 
    serial_use->write(0xFF); delay(1); //                      //

    for(uint8_t i = 0; i <= packet[1]; i++)
    { /* sending to data package */
      serial_use->write(packet[i]);
      checksum += packet[i];
      // delay(1);
    }
    serial_use->write(~checksum&0xFF); // ending to summation check 
    // delay(1);
  }
}
/*---------------------------------------- for joint mode ---------------------------------------*/
void DX::setSpeedMax(uint16_t spd_max) /* range speed joint setting */
{
  if(motor_mode == 1)
  {
    spd_maxRange = spd_max; // max speed of speed mapping
  }
}
void DX::setPosRange(int16_t pos_min, uint16_t pos_max) /* position range joint setting */
{
  if(motor_mode == 1)
  {
    pos_minRange = pos_min;
    pos_maxRange = pos_max;
  }
}
void DX::setPosLimit(int16_t limit_min, int16_t limit_max) /* safety position range setting */
{
  if(motor_mode == 1)
  {
    pos_minLimit = limit_min;
    pos_maxLimit = limit_max;
  }    
}
void DX::rotate(int16_t spd, int16_t pos) /* control joint mode rotation */
{
  if(motor_mode == 1)
  {
    uint16_t Packet[8] = {0}, // communication data package 
             checksum = 0;    // summation checking data package 
               
    spd = abs(spd);
    /* limit max speed and data mapping */
         if(spd > spd_maxRange) spd = spd_maxRange; 
    else if(spd < 0) spd = 0;
    spd = map(spd, 0, spd_maxRange, 0, 1023); 

    /* limit position range */
    if(pos >= 0)
    { 
      if(pos > pos_maxRange)  pos = pos_maxRange; 
    }
    else 
    {
      if(pos < pos_minRange)  pos = pos_minRange;
    }
    /* sefety position range and data mapping */   
         if(pos > pos_maxLimit) pos = pos_maxLimit; // limit motor max pos
    else if(pos < pos_minLimit) pos = pos_minLimit; // limit motor min pos
    pos = map(pos, pos_minRange, pos_maxRange, 0, 4095); 

  
    Packet[0] = id_motor;                  // motor id
    Packet[1] = 0x07;                      // lenght = instruction + 2
    Packet[2] = 0x03;                      // writing type
    Packet[3] = 0x1E;                      // address of goal position
    Packet[4] = byte(pos);                 // lowest byte position
    Packet[5] = byte((pos & 0x0F00) >> 8); // highest byte position (and 1111 0000 0000 shift 8 bit)
    Packet[6] = byte(spd);                 // lowest byte speed
    Packet[7] = byte((spd & 0x0300) >> 8); // highest byte speed

    /* starting to data package transmission */
    serial_use->write(0xFF); // header of the packet //
    serial_use->write(0xFF); //                      //
    
    for (unsigned int i = 0; i <= Packet[1]; i++)
    { /* sending to data package */
      serial_use->write(Packet[i]);
      checksum += Packet[i];
    }
    serial_use->write(~checksum & 0xFF);
  }
}
