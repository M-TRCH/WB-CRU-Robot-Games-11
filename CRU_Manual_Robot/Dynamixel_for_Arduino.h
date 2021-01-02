#include <Arduino.h>        //                          //
#include <SoftwareSerial.h> // arduino official library //                       
#include <Stream.h>         //                          // 

// *Communication Overview    >>  https://emanual.robotis.com/docs/en/dxl/protocol1/
// ROBOTIS e-Manual v1.31.30  >>  http://support.robotis.com/en/product/actuator/dynamixel/mx_series/mx-64at_ar.htm#Actuator_Address_20

class DX
{
  private:
    uint8_t  motor_mode   =  0;    // motor_mode = 1(joint mode), = 2(wheel mode) 
    uint8_t  id_motor     = -1;    // motor identity 
    uint16_t spd_maxRange =  1023; // default speed min value
    int16_t  spd_minRange = -1023; // default speed max value
    uint16_t pos_maxRange =  360;  // default position min value
    int16_t  pos_minRange =  0;    // default position max value
    int16_t  pos_maxLimit =  360;  // default position limit value
    int16_t  pos_minLimit =  0;    // default position limit value
  public:
    DX(); ~DX();
    void setMode(String mode);
    void setID(uint8_t id);
    void begin(SoftwareSerial *serial_arg, unsigned long baudrate);
    void begin(HardwareSerial *serial_arg, unsigned long baudrate);
    void setSpeedRange(int16_t spd_min, uint16_t spd_max);
    void setPosRange(int16_t pos_min, uint16_t pos_max);
    void setPosLimit(int16_t limit_min, int16_t limit_max);
    void setSpeedMax(uint16_t spd_max);
    void rotate(int16_t spd);
    void rotate(int16_t spd, int16_t pos);   
  protected:
    Stream *serial_use; // define steam object for communication
};
