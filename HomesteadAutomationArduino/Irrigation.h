#ifndef Irrigation_h
#define Irrigation_h
#include "Arduino.h"
#include "Device.h"
#include "IrrigationTimes.h"
#include "time.h"
#define NUM_IRRIGATION_TIMES 10

class Irrigation : public Device {
  public:
    Irrigation(int id, int pin, char newName[20], bool daysOfWeekToIrrigate[7], IrrigationTimes irrigationTimes[NUM_IRRIGATION_TIMES]); 
    bool isDayToIrrigate();
    const char* getType();
    void runDevice() override;

  private:
    const char *deviceType = "irrigation";
    bool daysOfWeekToIrrigate[7];
    IrrigationTimes irrigationTimes[NUM_IRRIGATION_TIMES];
};

#endif
