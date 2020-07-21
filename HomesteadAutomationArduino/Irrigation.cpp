#include "Irrigation.h"

Irrigation::Irrigation(int id, int pin, char newName[20], bool newDaysOfWeekToIrrigate[7], IrrigationTimes newIrrigationTimes[NUM_IRRIGATION_TIMES])
    : Device(id, pin, newName) {
  memcpy(this->daysOfWeekToIrrigate, newDaysOfWeekToIrrigate, sizeof(this->daysOfWeekToIrrigate));
  memcpy(this->irrigationTimes, newIrrigationTimes, sizeof(this->irrigationTimes));
}

const char* Irrigation::getType() {
  return this->deviceType;
}

bool Irrigation::isDayToIrrigate() {
  time_t rawtime;
  rawtime = time(NULL);
  struct tm *today = localtime(&rawtime);
  int dayToday = today->tm_wday;
  if (this->daysOfWeekToIrrigate[dayToday] == true) 
    return true;

  return false;
}

void Irrigation::runDevice() {
  if (this->isDayToIrrigate() && this->isOn()) {
    for (int i = 0; i < NUM_IRRIGATION_TIMES; i++) {
      time_t timeNow = time(NULL);
      time_t timeToStart = irrigationTimes[i].timeOn;
      time_t timeToStop = timeToStart + irrigationTimes[i].secondsToIrrigate;
      changeTimeToTodaysDate(timeToStart);
      changeTimeToTodaysDate(timeToStop);
      double timeDifference = difftime(timeToStop, timeToStart);

      if (timeDifference > 0) {
        if (timeNow > timeToStart && timeNow < timeToStop) {
          if (isOn())
            turnOn();
        } else {
          turnOff();
        }
      } else {
        if (timeNow > timeToStart || timeNow < timeToStop) {
          if (isOn())
            turnOn();
        } else {
          turnOff();
        }
      }
    }
  }
}
