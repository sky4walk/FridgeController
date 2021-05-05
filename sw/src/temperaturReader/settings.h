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
      mKalT = 0.0f;
      mKalM = 1.0f;
    }
    float getKalT() 
    {
      return mKalT;
    }
    void getKalT(float kaltT) 
    {
      mKalT = kaltT;
    }
    float getKalM() 
    {
      return mKalM;
    }
    void getKalM(float kaltM) 
    {
      mKalM = kaltM;
    }
  private:
    float mKalT;
    float mKalM;
};
#endif
