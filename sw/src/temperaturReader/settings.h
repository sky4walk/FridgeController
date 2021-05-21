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
      params.mKalT  =  0.0f;
      params.mKalM  =  1.0f;
      params.mOnT   =  26.1f;
      params.mOffT  =  27.1f;
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
    } params;
};
#endif
