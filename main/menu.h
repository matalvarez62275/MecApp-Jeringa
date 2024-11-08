#ifndef MENU_H
#define MENU_H

#include <LiquidCrystal_I2C.h>

// FSM states
enum State {
  MAIN_MENU,
  SET_FLOW_RATE,
  SET_VOLUME,
  START_INFUSION
};

/**
 * @brief Displays the menu on the LCD screen.
 * 
 * This function updates the LCD screen with the current menu options based on the 
 * provided state and input buffer.
 * 
 * @param lcd Reference to the LiquidCrystal_I2C object used to control the LCD screen.
 * @param currentState The current state of the application, which determines the menu options to display.
 * @param inputBuffer A reference to a string that holds the current user input.
 */
void displayMenu(LiquidCrystal_I2C& lcd, State currentState, String& inputBuffer);

/**
 * @brief Scrolls through the menu displayed on the LCD.
 * 
 * This function handles the scrolling of the menu items on the LCD screen.
 * It updates the display based on the current state of the menu.
 * 
 * @param lcd Reference to the LiquidCrystal_I2C object controlling the LCD.
 * @param currentState The current state of the menu, which determines the menu item to be displayed.
 */
void scrollMenu(LiquidCrystal_I2C& lcd, State currentState);

#endif /* MENU_H */