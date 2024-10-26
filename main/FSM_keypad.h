  #ifndef FSM_KEYPAD_H
  #define FSM_KEYPAD_H

  #include <Arduino.h>
  #include <Keypad.h>
  #include <LiquidCrystal_I2C.h>

  #define ROWS 4 // Four rows
  #define COLS 4 // Four columns

  #define LOW 0
  #define HIGH 1
  
  // FSM states
  enum State {
    MAIN_MENU,
    SET_FLOW_RATE,
    SET_VOLUME,
    START_INFUSION,
    STOP_INFUSION
  };

  void displayMenu(void);

  void scrollMenu(void);

  void handleEvent(char);
  
  #endif /* FSM_KEYPAD_H */