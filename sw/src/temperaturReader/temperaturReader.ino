#include "tempsensor.h"
#include "settings.h"
#include "controllerHysterese.h"
#include "Led.h"

#define GPIO5_D1 5
#define GPIO4_D2 4

Settings datas;
TemperaturSensorDS18B20 tmpSensor(GPIO4_D2,datas);
ControllerHysterese controlTmp(datas);
Led led(GPIO5_D1);

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);
  // Start the DS18B20 sensor
  tmpSensor.begin();
  controlTmp.begin();
  led.begin();
}

void loop() {
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
