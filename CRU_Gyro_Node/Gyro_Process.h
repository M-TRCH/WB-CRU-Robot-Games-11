#include <Arduino.h> // arduino official library //

class gyro
{
	private:
	  bool dmpReady = false; 
    uint8_t mpuIntStatus, 
            devStatus, 
            fifoBuffer[64],
            teapotPacket[14] = { '$', 0x02, 0,0, 0,0, 0,0, 0,0, 0x00, 0x00, '\r', '\n' };
    int16_t  packetSize; 
    uint16_t fifoCount; 
    float euler[3], 
          ypr[3], 
          yaw   = 0, //                    //
          pitch = 0, // output euler value // 
          row   = 0; //                    //
    int16_t offset_aZ = 1500, //                      //
            offset_gX =  200, // default offset value //
            offset_gY =   75, //                      //
            offset_gZ =  -85; //                      //         
    float first_yaw,
          second_yaw, 
          setpoint;
  public:
    gyro(); ~gyro();
    volatile bool mpuInterrupt = false; 
    void setOffset(int16_t set_aZ, int16_t set_gX, int16_t set_gY, int16_t set_gZ);
    void initial();
    void setSetpoint();
    void prepare(unsigned long interval_timeCheck, unsigned long timeout);
    float getVal(bool getProcess_value);
    float getVal();
};
