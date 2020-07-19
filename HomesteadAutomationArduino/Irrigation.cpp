#include "Irrigation.h"

Irrigation::Irrigation(int id, int pin, char newName[20], bool newDaysOfWeekToIrrigate[7], IrrigationTimes newIrrigationTimes[NUM_IRRIGATION_TIMES])
    : Device(id, pin, newName) {
  memcpy(this->daysOfWeekToIrrigate, newDaysOfWeekToIrrigate, sizeof(this->daysOfWeekToIrrigate));
  memcpy(this->irrigationTimes, newIrrigationTimes, sizeof(this->irrigationTimes));
}
