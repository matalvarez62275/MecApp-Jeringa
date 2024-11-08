#ifndef ACTIONS_H
#define ACTIONS_H

#include <Arduino.h>
#include <cmath>
#include "A4988.h"

#define DIR 32
#define STEP 33

void start_infusion(A4988& stepper, double speed, double pos);

#endif /* ACTIONS_H */