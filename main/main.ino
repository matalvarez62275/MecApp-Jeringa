#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include "menu.h"
#include "ultrasonic.h"
#include "actions.h"
#include "InfraredSensor.h"

#define LIMIT_SWITCH_BACK 34
#define LIMIT_SWITCH_FRONT 35

#define EMERGENCY_STOP 23

#define LED_IR 2
#define SENSOR_PIN A0

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Connect to the column pinouts of the keypad
byte colPins[COLS] = { 16, 4, 13, 14 };

// Connect to the row pinouts of the keypad
byte rowPins[ROWS] = { 19, 18, 5, 17 };

// Define the Keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Define the LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define the Stepper
StepperDriver stepper(STEP, DIR, 0);

// Define the INfrared Sensor
InfraredSensor irSensor(LED_IR, SENSOR_PIN, 10);

// Define the FSM
State currentState = MAIN_MENU;
int flowRate = 0;
int32_t volume = 0;
int syringe_length = 0;
int syringe_diameter = 0;
String inputBuffer = "";

void IRAM_ATTR stop() {
  stepper.stop();
}

void setup() {
  Serial.begin(115200);
  Serial.println("Hello World!");

  // Stepper Driver pin config
  stepper.begin();

  // Infrared Sensor pin config
  irSensor.begin();

  // Ultrasonic Sensor pin config
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);

  // LCD initialization
  lcd.init();
  lcd.backlight();
  
  // Limit Switch pin config
  pinMode(LIMIT_SWITCH_BACK, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(LIMIT_SWITCH_BACK), stop, RISING);
  
  pinMode(LIMIT_SWITCH_FRONT, INPUT_PULLDOWN);  
  attachInterrupt(digitalPinToInterrupt(LIMIT_SWITCH_FRONT), stop, RISING);

  // Emergency
  pinMode(EMERGENCY_STOP, INPUT);  
  attachInterrupt(digitalPinToInterrupt(EMERGENCY_STOP), stop, FALLING);

  displayMenu(currentState);
}

void loop() { 
  char key = keypad.getKey();
  if (key) {
    handleEvent(key);
  }
  scrollMenu(currentState);
}

void handleEvent(char key) {
  switch (currentState) {
    case MAIN_MENU:
      if (key == '1') {
        currentState = SET_FLOW_RATE;
      } else if (key == '2') {
        currentState = SET_VOLUME;
      } else if (key == '3') {
        currentState = START_INFUSION;
      } else if (key == '4') {
        currentState = SET_SYRINGE;
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
        start_infusion(flowRate, volume);
        delay(2000);
        currentState = MAIN_MENU;
      } else if (key == '*') {
        currentState = MAIN_MENU;
      }
      break;
    case SET_SYRINGE:
      stepper.setSpeed(DEFAULT_SPEED);
      Serial.println(key);
      if(key == 'D') {
        stepper.setSteps(-2000);
        delay(200);
        stepper.start();
      } else if(key == 'A') {
        stepper.setSteps(2000);
        delay(200);
        stepper.start();
      } else if(key == '#') {
        syringe_length = dist_in_mm();
        syringe_diameter = irSensor.getDistanceMM();
        Serial.println(syringe_diameter);
        currentState = MAIN_MENU;
      }
      break;
  }
  
  displayMenu(currentState);
}