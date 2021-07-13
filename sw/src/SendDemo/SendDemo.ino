/*
  Example for different sending methods
  
  https://github.com/sui77/rc-switch/
  
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {

  Serial.begin(115200);
  
  // WiiMo D1 moni D3  
  mySwitch.enableTransmit(0);
  mySwitch.setProtocol(1);
  mySwitch.setPulseLength(315);  
  mySwitch.setRepeatTransmit(3);  
}

void loop() {
  /* Same switch as above, but using decimal code */
  Serial.println("on");
  mySwitch.send(1631343, 24);
  delay(2500);  
  Serial.println("off");
  mySwitch.send(1631342, 24);
  delay(2500);   
}
