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
    void setSSID(String ssid)
    {
      params.ssid = ssid;    
    }
    String getSSID()
    {
      return params.ssid;    
    }
    void setPsk(String psk)
    {
      params.psk = psk;    
    }
    String getPsk()
    {
      return params.psk;    
    }
    void setNameDev(String nameDev)
    {
      params.nameDev = nameDev;    
    }
    String getNameDev()
    {
      return params.nameDev;    
    }
    void setServer(String server)
    {
      params.server = server;    
    }
    String getServer()
    {
      return params.server;    
    }
    void setUsername(String username)
    {
      params.username = username;    
    }
    String getUsername()
    {
      return params.username;    
    }
    void setPassWd(String passwd)
    {
      params.passwd = passwd;    
    }
    String getPassWd()
    {
      return params.passwd;    
    }
    void setPort(uint16_t port)
    {
      params.port = port;    
    }
    uint16_t getPort()
    {
      return params.port;    
    }
  private:
    
    struct
    {
      float mKalT;
      float mKalM;
      float mOnT;
      float mOffT;
      bool doubleReset;
      String ssid;
      String psk;
      String nameDev;
      String server;
      String username;
      String passwd;
      uint16_t port;
      
    } params;
};
#endif
