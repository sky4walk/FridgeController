#include <RCSwitch.h>
#include "tempsensor.h"
#include "settings.h"
#include "controllerHysterese.h"
#include "Led.h"
#include "DoubleResetDetector.h"

#define GPIO5_D1 5
#define GPIO4_D2 4
#define DRD_ADDRESS 0
#define DRD_TIMEOUT 10

Settings datas;
RCSwitch mySwitch = RCSwitch();
TemperaturSensorDS18B20 tmpSensor(GPIO4_D2,datas);
ControllerHysterese controlTmp(datas);
Led led(GPIO5_D1);
DoubleResetDetector drd(DRD_TIMEOUT, DRD_ADDRESS);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);

  if (drd.detectDoubleReset()) {
    Serial.println("Double Reset Detected");
    digitalWrite(LED_BUILTIN, LOW);
  } else {
    Serial.println("No Double Reset Detected");
    digitalWrite(LED_BUILTIN, HIGH);
  }
  
  tmpSensor.begin();
  controlTmp.begin();
  led.begin();
}

void loop() {
  if ( drd.doubleResetDetected ) {
  } else {
    float temperatureC = tmpSensor.getTemperatur();
    bool st = controlTmp.getState(temperatureC);
    led.set(st);
    Serial.print(temperatureC);
    Serial.println("ºC");
    if (st )
      Serial.println("on");
    else  
      Serial.println("off");
    delay(2000);
  }
  drd.loop();
}
