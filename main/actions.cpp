#include "actions.h"
#include <math.h>

// Function to start the infusion
void start_infusion(float flowrate, float volume) {
    // Calculate the cross-sectional area of the syringe (π * r^2)
    float radius = SYRINGE_DIAMETER / 2.0;
    float cross_sectional_area = M_PI * radius * radius; // mm^2

    Serial.print("flowrate: ");
    Serial.println(flowrate);
    Serial.print("volume: ");
    Serial.println(volume);

    // Convert flow rate from mL/h to mm^3/min
    float flowrate_mm3_per_min = (flowrate * 1000.0) / 60.0; // mm^3/min
    
    // Check if volume and/or flow rate are set
    if (volume > 0 && flowrate > 0) {
        // Both volume and flow rate are set
        float distance_to_travel = (volume * 1000.0) / cross_sectional_area; // mm
        int steps = static_cast<int>(distance_to_travel * STEPPER_STEPS / TRAVEL_PER_REV);
        float distance_per_minute = flowrate_mm3_per_min / cross_sectional_area; // mm/min
        float rpm = distance_per_minute * STEPPER_STEPS / TRAVEL_PER_REV; // steps per minute
        stepper.setSpeed(rpm);
        Serial.print("RPM: ");
        Serial.println(rpm);
        stepper.setSteps(-steps);
        Serial.print("Steps: ");
        Serial.println(steps);
        stepper.start();
    } else if (volume > 0) {
        // Only volume is set
        float distance_to_travel = volume / cross_sectional_area; // mm
        int steps = static_cast<int>(distance_to_travel * STEPPER_STEPS / TRAVEL_PER_REV);
        stepper.setSteps(-steps);
        Serial.print("Steps: ");
        Serial.println(steps);
        stepper.start();
    } else if (flowrate > 0) {
        // Only flow rate is set
        float distance_per_minute = flowrate_mm3_per_min / cross_sectional_area; // mm/min
        float rpm = distance_per_minute * STEPPER_STEPS / TRAVEL_PER_REV; // steps per minute
        stepper.setSpeed(rpm);
        Serial.print("RPM: ");
        Serial.println(rpm);
        stepper.start();
    } else {
        // Neither volume nor flow rate is set
        // Handle error or do nothing
    }
}