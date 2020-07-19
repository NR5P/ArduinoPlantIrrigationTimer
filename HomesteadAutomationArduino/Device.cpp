#include "Device.h"
#include "Arduino.h"

Device::Device(int id, int pin, char newName[]): id(id), pin(pin) {
  strcpy(this->deviceName, newName);
  pinMode(pin, OUTPUT);
}

bool Device::getPin() {
  return this->pin;
}

bool Device::setPin(int pin) {
  for (int i = 0; i < NUMOFDEVICES; i++) {
    if (Device::deviceList[i].getPin() == pin) {
      return false;
    }
  }
  this->pin = pin;
  return true;
}

bool Device::setName(char newName[20]) {
  if (strlen(newName) < 20) {
      strcpy(this->deviceName, newName);
      return true;
  }
  return false;
}

void Device::turnOff() {
  this->on = false;
}

void Device::turnOn() {
  this->on = true;
}

void Device::gpioOn() {
  if (this->on == true)
    digitalWrite(this->pin, HIGH);
}

void Device::gpioOff() {
  digitalWrite(this->pin, LOW);
}
