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


Menu::Menu() : encoder(A2, A3), lastPos(-1), lcd(0,1,2,3,4,5), button(6, PULLUP) {
  encoder.setPosition(0);
  displayMainMenu();
  lcd.begin(16,2);
}

// called once around every loop
void Menu::displayMenu() {
  updateEncoder();
  bool longOrShortPress = checkForLongPress(); //long press = true, short press = false, any other = null
  if (longOrShortPress != NULL && this->menuPosition == 0)
    this->menuPosition = 1;
  showMenuForMenuPosition();
}

void Menu::displayMainMenu() {
  const int itemCount = 3;
  rotaryMax = itemCount;
  char mainMenuItems[itemCount][20] = {"View Devices", "Add Device", "Set Time and Date"};
}

void Menu::displayCurrentDateTime() {
  
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

  if (lastPos != newPos) {
    lastPos = newPos;
  } // if
}

bool Menu::checkForLongPress() {
    if (button.isPressed() && !button.wasPressed())
      lastButtonPress = time(NULL);
    if (difftime(time(NULL),lastButtonPress) > 5)
      return true;
    if (!button.isPressed() && button.wasPressed() && difftime(time(NULL),lastButtonPress) < 5)
      return false;
    return NULL;
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
