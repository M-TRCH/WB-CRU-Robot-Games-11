#include <Arduino.h> // arduino official library //

class holonomic
{
  private:
    #define root2divide2 0.70710678118f // square root 2 divided by 2 value
    #define degTorad 0.0174532925       // convert degree to radian
    #define radTodeg 57.2957795         // convert radian to degree 
    float first_spd  = 0.000f,          // first whell speed
          second_spd = 0.000f,          // second wheel speed
          third_spd  = 0.000f;          // third wheel speed
     uint8_t no_wheel = 0;              // number of wheel
  public:
    holonomic(); ~holonomic();
    void  setWheel(uint8_t num);
    void  GetthreewheelSPD(float velocity, float heading, float omega);
    float GetSpd(uint8_t no);
};
