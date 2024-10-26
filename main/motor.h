#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

#define DIR 32
#define STEP 33

#define CLOCKWISE 1
#define ANTICLOCKWISE 0


#define STEPS_PER_REV 200

void moveStepper(int velocity, bool direction);

#endif /* MOTOR_H */