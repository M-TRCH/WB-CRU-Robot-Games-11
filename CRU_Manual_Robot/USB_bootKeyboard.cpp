#include "USB_bootkeyboard.h"

void KbdRptParser::debugMode(boolean mode_)
{
  mode = mode_;
}
void KbdRptParser::PrintKey(boolean action, uint8_t key) /* print button key */
{
  button[key] = action;
  if(mode)
  {
    Serial.print("button[");
    Serial.print(key);
    Serial.print("}");
    Serial.print("\t: ");
    Serial.println(button[key]);
  }
};
void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key) /* key down event */
{
  PrintKey(true, key);
}
void KbdRptParser::OnKeyUp(uint8_t mod, uint8_t key) /* key up event */
{
  PrintKey(false, key);
}
