#ifndef ACTIONS_H
#define ACTIONS_H

#include <Arduino.h>
#include "Stepper.h"

#define DIR 32
#define STEP 33

#define SYRINGE_VOLUME 50       // mL
#define SYRINGE_DIAMETER 29.4   // mm
#define SYRINGE_LENGTH 133      // mm


#define STEPPER_STEPS 200
#define TRAVEL_PER_REV 8    // mm

#define DEFAULT_SPEED 60    // RPM
#define MAX_SPEED 150       // RPM
#define STEPS_PER_FULL_STROKE (STEPPER_STEPS * SYRINGE_LENGTH / TRAVEL_PER_REV)
#define VOLUME_PER_STEP (SYRINGE_VOLUME / STEPS_PER_FULL_STROKE)

extern StepperDriver stepper;

void start_infusion(float flowRate, float volume);

#endif /* ACTIONS_H */