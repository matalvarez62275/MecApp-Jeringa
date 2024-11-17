#include "Stepper.h"

StepperDriver *instance = nullptr; // Single instance for interrupt handling

StepperDriver::StepperDriver(uint8_t stepPin, uint8_t dirPin, uint8_t timer)
    : _stepPin(stepPin), _dirPin(dirPin), _timer(timer), _hwTimer(nullptr),
      _remainingSteps(0), _running(false), _stepInterval(0), _lastStepTime(0), direction(0) {}

void StepperDriver::begin() {
    pinMode(_stepPin, OUTPUT);
    pinMode(_dirPin, OUTPUT);
    digitalWrite(_stepPin, LOW);
    digitalWrite(_dirPin, LOW);

    _hwTimer = timerBegin(_timer, 80, true); // Timer at 1 MHz (80 MHz / 80)
    timerAttachInterrupt(_hwTimer, &StepperDriver::onTimer, true);
    timerAlarmWrite(_hwTimer, 1000, true);  // Default alarm interval
    timerAlarmEnable(_hwTimer);

    instance = this;
}

void StepperDriver::setSpeed(float rpm) {
    if (rpm <= 0) {
        _stepInterval = 0;
    } else {
        _stepInterval = 60000000 / (200 * rpm); // Assuming 200 steps per revolution
    }
}

void StepperDriver::setSteps(int32_t steps) {
    _remainingSteps = abs(steps);
    digitalWrite(_dirPin, steps > 0 ? HIGH : LOW);
    direction = steps > 0 ? HIGH : LOW;
}

void StepperDriver::start() {
    _running = true;
}

void StepperDriver::stop() {
    _running = false;
}

bool StepperDriver::isRunning() {
    return _running;
}

bool StepperDriver::getDirection(){
    return direction;
}

void IRAM_ATTR StepperDriver::onTimer() {
    if (instance) {
        instance->handleStep();
    }
}

void StepperDriver::handleStep() {
    if (!_running || _remainingSteps == 0 || _stepInterval == 0) {
        return;
    }

    uint32_t currentTime = micros();
    if (currentTime - _lastStepTime >= _stepInterval) {
        digitalWrite(_stepPin, HIGH);
        delayMicroseconds(1);
        digitalWrite(_stepPin, LOW);
        _lastStepTime = currentTime;

        if (_remainingSteps > 0) {
            _remainingSteps--;
        }

        if (_remainingSteps == 0) {
            stop();
        }
    }
}
