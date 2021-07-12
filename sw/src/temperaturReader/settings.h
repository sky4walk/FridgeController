// brausteuerung@AndreBetz.de
#ifndef __SETTINGS__
#define __SETTINGS__

#include <Arduino.h>
///////////////////////////////////////////////////////////////////////////////
// Temperatur Sensoren DS18B20
///////////////////////////////////////////////////////////////////////////////
class Settings
{
  public:
    Settings()
    {
      params.mKalT              = 0.0f;
      params.mKalM              = 1.0f;
      params.mOnT               = 26.1f;
      params.mOffT              = 27.1f;
      params.onOff              = false;
      params.shouldSave         = false;
      params.switchOn           = 1631343;
      params.switchOff          = 1631342;
      params.switchProtocol     = 1;
      params.switchPulseLength  = 315;
      params.switchBits         = 24;
      params.switchRepeat       = 15;
    }
    float getKalT() 
    {
      return params.mKalT;
    }
    void setKalT(float kaltT) 
    {
      params.mKalT = kaltT;
    }
    float getKalM() 
    {
      return params.mKalM;
    }
    void setKalM(float kaltM) 
    {
      params.mKalM = kaltM;
    }
    float getOnT() 
    {
      return params.mOnT;
    }
    void setOnT(float onT) 
    {
      params.mOnT = onT;
    }
    float getOffT() 
    {
      return params.mOffT;
    }
    void setOffT(float offT) 
    {
      params.mOffT = offT;
    }
    void setWebPassWd(String webPassWd) {
      params.webPassWd = webPassWd;
    }
    String getWebPassWd() {
      return params.webPassWd;
    }
    float getActTemp(){
      return params.actTemp;
    }
    void setActTemp(float actTemp){
      params.actTemp = actTemp;
    }
    bool getOnOff() {
      return params.onOff;
    }
    void setOnOff(bool onOff) {
      params.onOff = onOff;
    }
    bool getShouldSave() {
      return params.shouldSave;
    }
    void setShouldSave(bool shouldSave) {
      params.shouldSave = shouldSave;
    }
    String getPassWd() {
      return params.passWd;
    }
    void setPassWd(String passWd) {
      params.passWd = passWd;
    }
    int getSwitchOn() {
      return params.switchOn;
    }
    int getSwitchOff() {
      return params.switchOff;
    }
    int getSwitchBits() {
      return params.switchBits;
    }
    int getSwitchProtocol() {
      return params.switchProtocol;
    }
    int getSwitchPulseLength() {
      return params.switchPulseLength;
    }
    int getSwitchRepeat() {
      return params.switchRepeat;
    }
  private:
    
    struct
    {
      float mKalT;
      float mKalM;
      float mOnT;
      float mOffT;
      bool doubleReset;
      String webPassWd;  
      float actTemp;
      bool onOff;
      bool shouldSave;
      String passWd;
      int switchOn;
      int switchOff;
      int switchProtocol;
      int switchPulseLength;
      int switchBits;
      int switchRepeat;
    } params;
};
#endif
