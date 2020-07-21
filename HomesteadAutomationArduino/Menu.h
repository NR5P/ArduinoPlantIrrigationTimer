#include <LiquidCrystal.h> 
#include "Button.h"
#include "RotaryEncoder.h"
#include "time.h"

class Menu {
  public:
    Menu();
    void displayMenu();

    

  private:
    const int waitSeconds = 5;
    RotaryEncoder encoder;
    LiquidCrystal lcd;
    Button button;
    int lastPos;
    time_t lastButtonPress;
    const int rotaryMin = 0;
    int rotaryMax;
    int menuPosition;
    
    char devicesMenuItems[10][20] = {"Irrigation", "Cycle Irrigation"};
    char irrigationMenu[10][20] = {"Pin", "Name", "Days of Week", "Irrigation Times"};
    char daysOfWeekMenu[7][10] = {"Monday", "Tuesday", "Wendesday", "Thursday", "Friday", "Saturday", "Sunday"};
    char irrigationTimesMenu[2][20] = {"Irrigation Time", "Irrigation Duration"};
    
    void updateEncoder();
    void displayMainMenu();
    void displayCurrentDateTime();
    bool checkForLongPress();
    void showMenuForMenuPosition();
    void setIdleState();
};
