#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include "motor.h"
#include "ultrasonic.h"
#include "FSM_keypad.h"


//IR
#define IR 2

//LCD
#define LCD_COLUMNS 16
#define LCD_ROWS 2
LiquidCrystal_I2C lcd(0x27, LCD_COLUMNS, LCD_ROWS);

void setup() {
  Serial.begin(115200);

  //configure pins
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);

  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);

  //configure LCD
  lcd.init();
  lcd.backlight();  // turn on LCD backlight

  displayMenu();
}

void loop() {
    /*char key = keypad.getKey();
    if (key) {
      handleEvent(key);
    }
    scrollMenu();*/
}


