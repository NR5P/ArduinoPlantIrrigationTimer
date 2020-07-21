#ifndef Device_h
#define Device_h
#include "time.h"
#define NUMOFDEVICES 10

class Device {
  public:
    Device(int id, int pin, char newName[]);
    bool setPin(int pin, Device* deviceList[]);
    bool setName(char newName[]);
    int getId();
    bool isOn();
    void turnOff();
    void turnOn();
    void gpioOn();
    void gpioOff();
    time_t changeTimeToTodaysDate(time_t &modifyTime);
    virtual void runDevice() = 0;
    
    static void runAllDevices();
  private:
    int id;
    int pin;
    char deviceName[20];
    bool currentState;
    bool on;
    bool getPin();
    
};

#endif
