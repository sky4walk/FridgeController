// brausteuerung@AndreBetz.de
#ifndef __WIFICONFIGURATION__
#define __WIFICONFIGURATION__

#include <WiFiManager.h>
#include "settings.h"
#include "DbgConsole.h"

#define PORTALTIMEOUT 300
#define TKIDSIZE 40
#define APNAME "Temp Controller Zwieselbrau.de"

class WifiConfiguration {
  public:
    WifiConfiguration(Settings& set) :
       mSettings(set) {      
    }
    void begin(){
//      wifiManager.setConfigPortalTimeout(PORTALTIMEOUT);  
//      wifiManager.setBreakAfterConfig(true);    
      WiFiManagerParameter custom_password  ("password", "Password", mSettings.getPassWd().c_str(), TKIDSIZE);      
      wifiManager.addParameter(&custom_password);      
    }
    bool config()
    {    
      CONSOLELN(F("started Portal"));
      wifiManager.startConfigPortal(APNAME);
      CONSOLELN(F("set wifi config"));
      CONSOLELN(wifiManager.getConfigPortalSSID());     
      return true;
    }
    bool connect() {
      return wifiManager.autoConnect(APNAME);
    }
  private:
    WiFiManager wifiManager;
    Settings& mSettings;
};


#endif
