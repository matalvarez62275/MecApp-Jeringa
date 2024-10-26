#include "motor.h"

void moveStepper(int velocity, bool direction) {
  
  if(direction){
    digitalWrite(DIR, HIGH); //Spinning Clockwise
  }
  else{
    digitalWrite(DIR, LOW); // Spinning Anti-Clockwise
  }


  for (int i = 0; i < STEPS_PER_REV; i++) {
    digitalWrite(STEP, HIGH);
    delayMicroseconds(velocity);
    digitalWrite(STEP, LOW);
    delayMicroseconds(velocity);
  }
}