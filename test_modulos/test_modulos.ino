#include <LiquidCrystal_I2C.h>

//stepper
#define DIR 32
#define STEP 33

#define CLOCKWISE 1
#define ANTICLOCKWISE 0

const int steps_per_rev = 200;

void moveStepper(int velocity, bool direction);

//IR
#define IR 2

//ultrasonic
#define ECHO 25
#define TRIG 26

float dist_in_cm();

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
}

void loop() {
  float distance = dist_in_cm();

  lcd.setCursor(0, 0);
  lcd.print("Distance:");

  lcd.setCursor(0, 1);
  lcd.print(distance);

  delay(200);  // Delay between readings
}

float dist_in_cm() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);

  unsigned long time = pulseIn(ECHO, HIGH);

  float distance = (time / 29.00) / 2;  // Calculate the distance using the speed of sound (29.00µs per centimeter)

  return distance;
}

void moveStepper(int velocity, bool direction) {
  
  if(direction){
    digitalWrite(DIR, HIGH); //Spinning Clockwise
  }
  else{
    digitalWrite(DIR, LOW); // Spinning Anti-Clockwise
  }


  for (int i = 0; i < steps_per_rev; i++) {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(velocity);
    digitalWrite(STEP, LOW);
    delayMicroseconds(velocity);
  }
}