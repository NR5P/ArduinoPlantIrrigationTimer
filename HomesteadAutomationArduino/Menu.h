#ifndef Menu_h
#define Menu_h

#include <LiquidCrystal.h> 
#include "Button.h"
#include "RotaryEncoder.h"
#include "time.h"
#include "Device.h"

extern Device* deviceList[10];
extern int numDevices;

class Menu {
  static int lastPos;
  public:
    Menu();
    void displayMenu();

  private:
    enum MENU {
      CURRENT_DATE_TIME = 0,
      MAIN_MENU = 1,
      ADD_DEVICE_MENU = 3,
      IRRIGATION_MENU = 4,
      CYCLE_IRRIGATION_MENU = 5,
      PIN_SELECT = 6
    };

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
    int cursor2pos = 0;
    
    char *tempName[2];
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
    void displayNameSelect();
    int checkForLongPress();
    void checkButtonFlag();
    void showMenuForMenuPosition();
    void setIdleState();
    void splitTime(const char *dateTime,char *firstPart,char *secondPart);
};



#endif
