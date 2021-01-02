#include <Arduino.h> // arduino official library
#include <hidboot.h> //                                                                         //
#include <usbhub.h>  // library source on github : https://github.com/felis/USB_Host_Shield_2.0 //
#include <SPI.h>

class KbdRptParser : public KeyboardReportParser
{
  private:
    boolean mode = false;         // mode = true(seialprint working) = false(serialprint not working)
  public:
    boolean button[85] = {false}; // button action variables
    void PrintKey(boolean action, uint8_t key); 
    void debugMode(boolean mode_);
  protected:
    void OnKeyDown(uint8_t mod, uint8_t key);
    void OnKeyUp(uint8_t mod, uint8_t key);
};
