#ifndef Device_h
#define Device_h
#define NUMOFDEVICES 10

class Device {
  public:
    Device(int id, int pin, char newName[]);
    bool setPin(int pin);
    bool setName(char newName[]);
    void turnOff();
    void turnOn();
    void gpioOn();
    void gpioOff();

    static Device deviceList[10];
  private:
    int id;
    int pin;
    char deviceName[20];
    bool currentState;
    bool on;

    bool getPin();
};

#endif
