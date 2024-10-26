#include "ultrasonic.h"

float dist_in_cm() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);

  unsigned long time = pulseIn(ECHO, HIGH);

  float distance = (time / 29.00) / 2;  // Calculate the distance using the speed of sound (29.00µs per centimeter)

  return distance;
}