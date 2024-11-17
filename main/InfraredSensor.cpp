#include "InfraredSensor.h"

InfraredSensor::InfraredSensor(int ledPin, int sensorPin, int samples)
    : ledPin(ledPin), sensorPin(sensorPin), samples(samples), out(0) {
    sensorValue[0] = 0;
    sensorValue[1] = 0;
    sensorRead[0] = 0;
    sensorRead[1] = 0;
}

void InfraredSensor::begin() {
    pinMode(ledPin, OUTPUT);
}

int InfraredSensor::getDistanceMM() {
    int sensorRead = readIR();
    return convert2mm(sensorRead);
}

int InfraredSensor::readIR() {
    out = 0;
    sensorRead[0] = 0;
    sensorRead[1] = 0;
    sensorValue[0] = 0;
    sensorValue[1] = 0;

    for (int i = 0; i < samples; i++) {
        digitalWrite(ledPin, LOW);
        delay(2);
        sensorValue[0] = analogRead(sensorPin);
        digitalWrite(ledPin, HIGH);
        delay(2);
        sensorRead[0] = analogRead(sensorPin);
        sensorValue[1] += sensorValue[0];
        sensorRead[1] += sensorRead[0];
    }

    sensorValue[1] /= samples;
    sensorRead[1] /= samples;
    out = sensorRead[1] - sensorValue[1];

    return (out > 0) ? out : 0;
}

int InfraredSensor::convert2mm(int sensorValue) {
    int minSensorValue = 0;
    int maxSensorValue = 1023;
    int minDistanceMM = 0;
    int maxDistanceMM = 1000;

    // Map to mm
    return map(sensorValue, minSensorValue, maxSensorValue, minDistanceMM, maxDistanceMM);
}