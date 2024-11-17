#ifndef STEPPER_DRIVER_H
#define STEPPER_DRIVER_H

#include <Arduino.h>

class StepperDriver {
public:
    StepperDriver(uint8_t stepPin, uint8_t dirPin, uint8_t timer);
    void begin();
    void setSpeed(float rpm);
    void setSteps(int32_t steps);
    void start();
    void stop();
    bool isRunning();

    bool getDirection();

private:
    static void IRAM_ATTR onTimer();
    void handleStep();

    uint8_t _stepPin;
    uint8_t _dirPin;
    uint8_t _timer;
    hw_timer_t *_hwTimer;
    volatile int32_t _remainingSteps;
    volatile bool _running;
    volatile uint32_t _stepInterval; // In microseconds
    volatile uint32_t _lastStepTime;

    bool direction;
};

#endif
