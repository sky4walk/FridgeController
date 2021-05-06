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
  private:
    
    struct
    {
      float mKalT;
      float mKalM;
      float mOnT;
      float mOffT;
      bool doubleReset;
    } params;
};
#endif
