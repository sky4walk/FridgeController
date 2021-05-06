//#include <DNSServer.h>
//#include <ESP8266WebServer.h>
//#include <ESP8266WiFi.h> 
#include <RCSwitch.h>
#include "DbgConsole.h"
#include "tempsensor.h"
#include "settings.h"
#include "controllerHysterese.h"
#include "Led.h"
#include "DoubleResetDetector.h"
#include "WaitTime.h"
#include "SettingsLoader.h"
#include "WifiCofiguration.h"

#define GPIO5_D1 5
#define GPIO4_D2 4
#define DRD_ADDRESS 0
#define DRD_TIMEOUT 10
#define READ_TEMP  2*MIL2SEC


bool configMode = true;
Settings datas;
RCSwitch mySwitch = RCSwitch();
TemperaturSensorDS18B20 tmpSensor(GPIO4_D2,datas);
ControllerHysterese controlTmp(datas);
Led led(GPIO5_D1);
DoubleResetDetector drd(DRD_TIMEOUT, DRD_ADDRESS);
WaitTime sensorRead(READ_TEMP);
SettingsLoader loader(datas);
WifiConfiguration wifiConfig(datas);

void setup() {
  CONSOLELN(ESP.getSdkVersion());
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  wifiConfig.begin();
  
  configMode = false;

  if ( !loader.load() ) {
    loader.save();
  }

  if ( drd.detectDoubleReset() ) {
    CONSOLELN("Start web config");
    digitalWrite(LED_BUILTIN, LOW);
    configMode = true;
    wifiConfig.config();
    loader.save();
  } else {
    CONSOLELN("No Double Reset Detected");
    digitalWrite(LED_BUILTIN, HIGH);
    if (!wifiConfig.connect()) {
      configMode = true;
      loader.save();
    }
  }
  
  tmpSensor.begin();
  controlTmp.begin();
  led.begin();
  
}

void loop() {
  if ( ! configMode ) {
    sensorRead.start();
    if (sensorRead.timeOver()) {
      float temperatureC = tmpSensor.getTemperatur();
      bool st = controlTmp.getState(temperatureC);
      led.set(st);
      CONSOLE(temperatureC);
      CONSOLE("ºC");
      if (st )
        CONSOLELN(" on");
      else  
        CONSOLELN(" off");
      sensorRead.restart();
    }
  }
  drd.loop();
}
