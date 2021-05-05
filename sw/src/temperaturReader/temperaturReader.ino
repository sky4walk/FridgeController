#include "tempsensor.h"
#include "settings.h"
#include "controllerHysterese.h"

Settings datas;
TemperaturSensorDS18B20 tmpSenseor(4,datas);
ControllerHysterese controlTmp(datas);

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);
  // Start the DS18B20 sensor
  tmpSenseor.begin();
}

void loop() {
  float temperatureC = tmpSenseor.getTemperatur();
  Serial.print(temperatureC);
  Serial.println("ºC");
  delay(2000);
}
