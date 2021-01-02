#include "USB_bootkeyboard.h"
#define _CRU_JOYREADER_H_   
/*------------------------------------- parameter setting --------------------------------------*/
/* object define */
USB usb;
HIDBoot<USB_HID_PROTOCOL_KEYBOARD>HidKeyboard(&usb);
KbdRptParser parser;
/* setting */
#define readJoy_debugMode false
/* key parameter setting */
#define KEY_UP    82
#define KEY_DOWN  81
#define KEY_RIGTH 79
#define KEY_LEFT  80
#define KEY_ESC   41
#define KEY_F1    58
#define KEY_F2    59
#define KEY_F3    60
#define KEY_F4    61
#define KEY_F5    62
#define KEY_F6    63
#define KEY_F7    64
#define KEY_F8    65
#define KEY_F9    66
#define KEY_F10   67
#define KEY_DEL   76
#define KEY_WORM  53
#define KEY_1     30
#define KEY_2     31
#define KEY_3     32
#define KEY_4     33
#define KEY_5     34
#define KEY_6     35
#define KEY_7     36
#define KEY_8     37
#define KEY_9     38
#define KEY_0     39
#define KEY_TAP   43
#define KEY_Q     20
#define KEY_W     26
#define KEY_E      8
#define KEY_R     21
#define KEY_T     23
#define KEY_Y     28
#define KEY_U     24
#define KEY_I     12
#define KEY_O     18
#define KEY_P     19
#define KEY_SBACK 49
#define KEY_CAPS  57
#define KEY_A      4
#define KEY_S     22
#define KEY_D      7 
#define KEY_F      9
#define KEY_G     10
#define KEY_H     11
#define KEY_J     13
#define KEY_K     14
#define KEY_L     15
#define KEY_ENTER 40
#define KEY_Z     29
#define KEY_X     27
#define KEY_C      6
#define KEY_V     25
#define KEY_B      5
#define KEY_N     17
#define KEY_M     16
#define KEY_LESS  54 
#define KEY_OVER  55
#define KEY_COLON 51
#define KEY_RAT   52
#define KEY_LINE  45
#define KEY_ADD   46
#define KEY_SPACE 44
#define KEY_OPEN  47
#define KEY_CLOSE 48
#define KEY_QUEST 56
#define KEY_OK    40
#define KEY_PGUP  75
#define KEY_PGDN  78
/*-----------------------------------------------------------------------------------------------*/

void usbJoy_init() /* usb host keyboard initialize */
{
  if(usb.Init() == -1) Serial.println("OSC did not start");

  parser.debugMode(readJoy_debugMode); delay(500);
  HidKeyboard.SetReportParser(0, &parser);  
}
boolean oneTime_Set = true;
void button_Read() /* for debug mode (print key on keyboard) */
{
  if(oneTime_Set)
  {
    parser.debugMode(true); 
    oneTime_Set = false;
  }
  usb.Task();
}
boolean press(uint8_t num) /* press condition checking each key */
{
  usb.Task();
  return parser.button[num]; 
}
