#include "Device.h"
#include "Arduino.h"

Device::Device(int id, int pin, char newName[]): id(id), pin(pin) {
  strcpy(this->deviceName, newName);
  pinMode(pin, OUTPUT);
}

bool Device::setPin(int pin, Device* deviceList[]) {
  for (int i = 0; i < NUMOFDEVICES; i++) {
    if (deviceList[i]->getPin() == pin && deviceList[i]->getId() != this->getId()) {
      return false;
    }
  }
  this->pin = pin;
  return true;
}

int Device::getPin() {
  return this->pin;
}

int Device::getId() {
  return this->id;
}

bool Device::isOn() {
  return this->on;
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

time_t Device::changeTimeToTodaysDate(time_t &modifyTime) {
  time_t today;
  today = time(NULL);
  struct tm *todayStruct = localtime(&today);
  struct tm *timeToChange = localtime(&modifyTime);
  timeToChange->tm_mday = todayStruct->tm_mday;
  timeToChange->tm_mon = todayStruct->tm_mon;
  timeToChange->tm_year = todayStruct->tm_year;
  timeToChange->tm_wday = todayStruct->tm_wday;
  timeToChange->tm_yday = todayStruct->tm_yday;
  timeToChange->tm_isdst = todayStruct->tm_isdst;

  modifyTime = mktime(timeToChange);
  return modifyTime;
}
