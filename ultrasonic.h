#include <Arduino.h>
#include "samplebuffer.h"

#define MEASURE_DELAY 0

class UltrasonicSensor {
  public:
    void setPin(int pin);
    void update();
    double distance();
  private:
    int pin;
    unsigned long int lastMeasureTime;
    SampleBuffer samples;
};

void UltrasonicSensor::setPin(int _pin) {
  pin = _pin;
}

void UltrasonicSensor::update() {
  if ((millis() - lastMeasureTime) > MEASURE_DELAY) {
    lastMeasureTime = millis();
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delayMicroseconds(2);
    digitalWrite(pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(pin, LOW);
    pinMode(pin, INPUT);
    samples.push(pulseIn(pin, HIGH));
  }
}

double UltrasonicSensor::distance() {
  long int value = samples.getValue();
  double distance = value / 140.0;
  if ((distance == 0) || (distance >= 400.0)) {
    return 180.0;
  }
  return distance;
}