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
  if (longOrShortPress != 3 && this->menuPosition == 0) {
    lcd.clear();
    this->menuPosition = 1;
  }

  showMenuForMenuPosition();
}

void Menu::displayMainMenu() {
  const int itemCount = 3;
  rotaryMax = itemCount - 1;
  char mainMenuItems[itemCount][20] = {"View Devices", "Add Device", "Set Time and Date"};
  lcd.setCursor(0,0);
  lcd.print("Main Menu");
  lcd.setCursor(0,1);
  lcd.print(mainMenuItems[Menu::lastPos]);

  //if (this->longOrShortPress == false)
    //this->menuPosition = 2; TODO: check position of encoder
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
    //Serial.println(button.isPressed());
    if (!button.isPressed())
      newButtonPress = false;
    if (button.isPressed() && !newButtonPress) {
      lastButtonPress = millis() / 1000;
      newButtonPress = true;
    }
    if (lastButtonPress != NULL) {
      if (button.isPressed() && ((millis() / 1000) - lastButtonPress) > 3) {
        Serial.println("long press");
        lastButtonPress = NULL;
        return 1;
      }
      if (!button.isPressed() && ((millis() / 1000) - lastButtonPress) < 3) {
        Serial.println("short press");
        lastButtonPress = NULL;
        return 0;
      }
      return 3;
    }

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
  }
}

void Menu::splitTime(const char *dateTime,char *firstPart,char *secondPart) {
  for (int i = 0; i < 10; i++) 
    *(firstPart + i) = *(dateTime + i);
  for (int i = 10; i < 24; i++)
    *(secondPart + i - 11) = *(dateTime + i);
  *(secondPart + 13) = '\0';
}
