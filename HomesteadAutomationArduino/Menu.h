#ifndef Menu_h
#define Menu_h

#include <LiquidCrystal.h> 
#include "Button.h"
#include "RotaryEncoder.h"
#include "time.h"
#include "Device.h"

extern Device* deviceList[10];

class Menu {
  static int lastPos;
  public:
    Menu();
    void displayMenu();

  private:
    const int waitSeconds = 5;
    RotaryEncoder encoder;
    LiquidCrystal lcd;
    Button button;
    bool newButtonPress;
    
    long int lastButtonPress;
    int rotaryMin = 0;
    int rotaryMax;
    int menuPosition;
    int lastMenuPosition;
    int longOrShortPress;
    
    char devicesMenuItems[10][20] = {"Irrigation", "Cycle Irrigation"};
    char irrigationMenu[10][20] = {"Pin", "Name", "Days of Week", "Irrigation Times"};
    char daysOfWeekMenu[7][10] = {"Monday", "Tuesday", "Wendesday", "Thursday", "Friday", "Saturday", "Sunday"};
    char irrigationTimesMenu[2][20] = {"Irrigation Time", "Irrigation Duration"};
    
    void updateEncoder();
    void displayMainMenu();
    void displayCurrentDateTime();
    void displayAddDeviceMenu();
    void displayIrrigationMenu();
    void displayCycleIrrigationMenu();
    void displayPinSelect();
    int checkForLongPress();
    void checkButtonFlag();
    void showMenuForMenuPosition();
    void setIdleState();
    void splitTime(const char *dateTime,char *firstPart,char *secondPart);
};



#endif
