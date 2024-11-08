#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include "stateMachine.h"
#include "menu.h"
#include "ultrasonic.h"

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Connect to the column pinouts of the keypad
byte colPins[COLS] = { 16, 4, 14, 13 };

// Connect to the row pinouts of the keypad
byte rowPins[ROWS] = { 19, 18, 5, 17 };

// Define the Keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Define the LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define the Stepper
A4988 stepper(200, 32, 33);

State currentState = MAIN_MENU;
String inputBuffer = "";


void setup() {
  Serial.begin(115200);

  // Stepper Driver pin config
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);

  // Ultrasonic Sensor pin config
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);

  // LCD initialization
  lcd.init();
  lcd.backlight();

  displayMenu(lcd, currentState, inputBuffer);
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    handleEvent(key, lcd, currentState, inputBuffer, stepper);
  }
  scrollMenu(lcd, currentState);
}