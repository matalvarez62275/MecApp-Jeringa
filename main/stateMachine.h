#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "actions.h"
#include "menu.h"

void handleEvent(char key, LiquidCrystal_I2C& lcd, State currentState, String& inputBuffer, A4988 &stepper);

#endif /* STATEMACHINE_H */