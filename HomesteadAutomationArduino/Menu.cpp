#include "Menu.h"
#include "RotaryEncoder.h"
#include "Arduino.h"

//lcd.setCursor(column,row0or1);
//lcd.print();
//lcd.clear();
//lcd.blink(); to blink cursor
//lcd.noBlink();
//lcd.cursor(); for other cursor underscore
//lcd.noCursor;

/*
 * byte slash[8] = {
 *  B00001,
 *  B00010,
 *  B00100,
 *  B01000,
 *  B10000,
 *  B00000,
 *  B00000,
 *  B00000,
 * }
 *lcd.createChar(7, slash); 0-7 custom chars
 *lcd.write(7);
 */

int Menu::lastPos = 0;


Menu::Menu() : encoder(A2, A3), lcd(A4,A5,7,8,4,5), button(6, PULLUP), longOrShortPress(3), menuPosition(0), lastButtonPress(-50) {
  encoder.setPosition(0);
  displayMainMenu();
  lcd.begin(16,2);
  Menu::lastPos = 0;
}

// called once around every loop
void Menu::displayMenu() {
  updateEncoder();
  this->longOrShortPress = checkForLongPress(); //long press = true, short press = false, any other = null
  if (longOrShortPress == 0 && this->menuPosition == 0) {
    lcd.clear();
    Menu::lastPos = 0;
    this->menuPosition = 1;
  }

  showMenuForMenuPosition();
}

void Menu::displayMainMenu() {
  const int itemCount = 4;
  rotaryMax = itemCount - 1;
  char mainMenuItems[itemCount][20] = {"","View Devices", "Add Device", "Set Time and Date"};
  lcd.setCursor(0,0);
  lcd.print("Main Menu");
  lcd.setCursor(0,1);
  lcd.print(mainMenuItems[Menu::lastPos]);
  if (longOrShortPress == 1 && this->menuPosition == 1) {
      this->menuPosition = 0;
      lcd.clear();
  }

  if (longOrShortPress == 0) {
    switch(Menu::lastPos) {
      case 0 : 
        break;
      case 1 :
        break;
      case 2 :
        this->menuPosition = 3;
        break;
      case 3 :
        break;
    }
    encoder.setPosition(0);
    lcd.clear();
  }
}

void Menu::displayAddDeviceMenu() {
  const int itemCount = 3;
  rotaryMax = itemCount - 1;
  char menuItems[itemCount][20] = {"","Irrigation", "CycleIrrigation"};
  lcd.setCursor(0,0);
  lcd.print("Add Device");
  lcd.setCursor(0,1);
  lcd.print(menuItems[Menu::lastPos]);
  if (longOrShortPress == 1) {
      this->menuPosition = 1;
      lcd.clear();
  }

  if (longOrShortPress == 0) {
    switch(Menu::lastPos) {
      case 0 : 
        break;
      case 1 :
        this->menuPosition = 4;
        break;
      case 2 :
        this->menuPosition = 5;
        break;
    }
    Menu::lastPos = 0;
    lcd.clear();
  }
}

void Menu::displayCurrentDateTime() {
  char datePart[10];
  char timePart[15];
  
  time_t currentTime;
  currentTime = time(NULL);
  char *timeString = ctime(&currentTime);
  splitTime(timeString, datePart, timePart);
  //lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(datePart);
  //lcd.print(timeString);
  lcd.setCursor(0,1);
  lcd.print(timePart);
}

void Menu::displayIrrigationMenu() {
  const int itemCount = 5;
  rotaryMax = itemCount - 1;
  char menuItems[itemCount][20] = {"","pin","name","days of week", "times & duration"};
  lcd.setCursor(0,0);
  lcd.print("Irrigation");
  lcd.setCursor(0,1);
  lcd.print(menuItems[Menu::lastPos]);
  if (longOrShortPress == 1) {
      this->menuPosition = 3;
      lcd.clear();
  }

  if (longOrShortPress == 0) {
    switch(Menu::lastPos) {
      case 1 : 
        this->menuPosition = 6;
        break;
    }
    Menu::lastPos = 0;
  }
}

void Menu::displayCycleIrrigationMenu() {
  const int itemCount = 7;
  rotaryMax = itemCount - 1;
  char menuItems[itemCount][20] = {"","pin","name","cycle on time", "cycle off time", "blackout start", "blackout stop"};
  lcd.setCursor(0,0);
  lcd.print("Cycle Irrigation");
  lcd.setCursor(0,1);
  lcd.print(menuItems[Menu::lastPos]);
  if (longOrShortPress == 1) {
      this->menuPosition = 3;
      lcd.clear();
  }
}

void Menu::displayPinSelect() {
  const int lowPin = 22;
  const int highPin = 53;
  rotaryMin = lowPin;
  rotaryMax = highPin;
  bool pinUsed = false;
  lcd.setCursor(0,0);
  lcd.print("select avail pin");
  lcd.setCursor(0,1);
  for (Device *d : deviceList) {
    if (Menu::lastPos == d->getPin()) {
      pinUsed = true;
    }
  }
  lcd.print(Menu::lastPos);
  if (pinUsed == false) {
    lcd.println("-available");
  }
  else {
    lcd.println("-used");
  }
}

void Menu::updateEncoder() {
  encoder.tick();
  // get the current physical position and calc the logical position
  int newPos = encoder.getPosition();

  if (newPos < rotaryMin) {
    encoder.setPosition(rotaryMin);
    newPos = rotaryMin;

  } else if (newPos > rotaryMax) {
    encoder.setPosition(rotaryMax);
    newPos = rotaryMax;
  } // if

  if (Menu::lastPos != newPos) {
    lcd.clear();
    Menu::lastPos = newPos;
  } // if
}

int Menu::checkForLongPress() {
    if (!button.isPressed())
      newButtonPress = false;
    if (button.isPressed() && !newButtonPress) {
      lastButtonPress = millis() / 1000;
      newButtonPress = true;
    }
    if (lastButtonPress != NULL) {
      if (button.isPressed() && ((millis() / 1000) - lastButtonPress) > 2) {
        lastButtonPress = NULL;
        return 1;
      }
      if (!button.isPressed() && ((millis() / 1000) - lastButtonPress) < 2) {
        lastButtonPress = NULL;
        return 0;
      }
    }
    return 3;
}

void Menu::setIdleState() {
  if (difftime(time(NULL),this->lastButtonPress) > 10)
    this->menuPosition = 0;
}

void Menu::showMenuForMenuPosition() {
  switch(this->menuPosition) {
    case 0 :
      displayCurrentDateTime();
      break;
    case 1 :
      displayMainMenu();
      break;
    case 2 :
      displayMainMenu();
      break;
    case 3 :
      displayAddDeviceMenu();
      break;
     case 4 :
      displayIrrigationMenu();
      break;
     case 5 :
      displayCycleIrrigationMenu();
      break;
     case 6 :
      displayPinSelect();
      break;
  }
}

void Menu::splitTime(const char *dateTime,char *firstPart,char *secondPart) {
  for (int i = 0; i < 10; i++) 
    *(firstPart + i) = *(dateTime + i);
  for (int i = 10; i < 24; i++)
    *(secondPart + i - 11) = *(dateTime + i);
  *(secondPart + 13) = '\0';
}
