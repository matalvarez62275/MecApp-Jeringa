#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>

#define ECHO 25
#define TRIG 26

float dist_in_mm(void);

#endif /* ULTRASONIC_H */