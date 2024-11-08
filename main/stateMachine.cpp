#include "stateMachine.h"
#include <LiquidCrystal_I2C.h>

void handleEvent(char key, LiquidCrystal_I2C& lcd, State currentState, String& inputBuffer, A4988& stepper) {
  static int flowRate = 0;
  static int volume = 0;
  switch (currentState) {
    case MAIN_MENU:
      if (key == '1') {
        currentState = SET_FLOW_RATE;
      } else if (key == '2') {
        currentState = SET_VOLUME;
      } else if (key == '3') {
        currentState = START_INFUSION;
      }
      break;
    case SET_FLOW_RATE:
      if (key == '#') {
        flowRate = inputBuffer.toInt();
        inputBuffer = "";
        currentState = MAIN_MENU;
      } else if (key == '*') {
        inputBuffer = "";
        currentState = MAIN_MENU;
      } else {
        inputBuffer += key;
      }
      break;
    case SET_VOLUME:
      if (key == '#') {
        volume = inputBuffer.toInt();
        inputBuffer = "";
        currentState = MAIN_MENU;
      } else if (key == '*') {
        inputBuffer = "";
        currentState = MAIN_MENU;
      } else {
        inputBuffer += key;
      }
      break;
    case START_INFUSION:
      if (key == '#') {
        lcd.clear();
        lcd.print("Infusion started");
        start_infusion(stepper, flowRate, volume);
        delay(2000);
        currentState = MAIN_MENU;
      } else if (key == '*') {
        currentState = MAIN_MENU;
      }
      break;
  }
  
  displayMenu(lcd, currentState, inputBuffer);
}