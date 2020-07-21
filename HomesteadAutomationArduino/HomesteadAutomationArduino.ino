#include "Device.h"
#include "Menu.h"
#include "Arduino.h"

Device* deviceList[10];
Menu menu;

void setup() {
  
}

void loop() {
  for (int i = 0; i < NUMOFDEVICES; i++) {
    deviceList[i]->runDevice();
  }

  menu.displayMenu();
}
