#ifndef INFRARED_SENSOR_H
#define INFRARED_SENSOR_H

#include <Arduino.h>

class InfraredSensor {
public:
    InfraredSensor(int ledPin, int sensorPin, int samples = 10);
    void begin();
    int getDistanceMM();

private:
    int readIR();
    int convert2mm(int sensorValue);

    int ledPin;
    int sensorPin;
    int samples;
    int out;
    int sensorValue[2];
    int sensorRead[2];
};

#endif