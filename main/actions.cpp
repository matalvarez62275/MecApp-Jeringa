#include "actions.h"
#include "ultrasonic.h"

#define CLOCKWISE 1
#define ANTICLOCKWISE 0

#define STEPPER_STEPS 200
#define TRAVEL_PER_REV 8    // mm
#define SYRINGE_LENGTH 50   // mm
#define SYRINGE_VOLUME 10   // mL
#define DEFAULT_SPEED 100   // RPM
#define STEPS_PER_FULL_STROKE (STEPPER_STEPS * SYRINGE_LENGTH / TRAVEL_PER_REV)
#define VOLUME_PER_STEP (SYRINGE_VOLUME / STEPS_PER_FULL_STROKE)

void start_infusion(A4988& stepper, double flowRate, double volume) {
    int steps_per_second = 0;
    int total_steps = 0;
    int rpm = 0;

    if (flowRate != 0 && volume == 0) {
        // Only flowRate is set
        steps_per_second = flowRate / VOLUME_PER_STEP;
        rpm = (steps_per_second * 60) / STEPPER_STEPS;
        stepper.begin(rpm, 2);
        while (dist_in_mm() <= 300) {
            stepper.move(1); // Move one step at a time
        }
    } else if (flowRate == 0 && volume != 0) {
        // Only volume is set
        total_steps = volume / VOLUME_PER_STEP;
        stepper.begin(DEFAULT_SPEED, 2);
        stepper.move(total_steps);
    } else if (flowRate != 0 && volume != 0) {
        // Both flowRate and volume are set
        steps_per_second = flowRate / VOLUME_PER_STEP;
        total_steps = volume / VOLUME_PER_STEP;
        rpm = (steps_per_second * 60) / STEPPER_STEPS; // Convert steps per second to RPM
        stepper.begin(rpm, 2);
        while (dist_in_mm() <= 300 && total_steps > 0) {
            stepper.move(1); // Move one step at a time
        }
    }
}