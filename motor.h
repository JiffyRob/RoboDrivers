#ifndef MOTORLIB
#define MOTORLIB

#include <Arduino.h>

enum Direction {
  forward,
  backward,
};

class Motor {
  public:
    void turn(int speed, Direction direction);
    void accel(int speed, Direction direction, int accelSpeed);
    void update();
    void stop();
    Motor(int p1, int p2);
    Motor();
  private:
    int p1;
    int p2;
    Direction dir;
    int currentSpeed;
    int targetSpeed;
    float accelSpeed;
};

Motor::Motor() {
  p1 = 0;
  p2 = 0;
  dir = forward;
  currentSpeed = 0;
  targetSpeed = 0.0;
  accelSpeed = 0.0;
}

Motor::Motor(int pin1, int pin2) {
  p1 = pin1;
  p2 = pin2;
  dir = forward;
  currentSpeed = 0;
  targetSpeed = 0;
  accelSpeed = 0.0;
}

void Motor::turn(int speed, Direction direction) {
  if ((speed == currentSpeed) && (direction == dir)) {
    return;
  }
  int pa, pb;
  switch (direction) {
    case forward:
      pa = p1;
      pb = p2;
      break;
    case backward:
      pa = p2;
      pb = p1;
      break;
  }
  digitalWrite(pa, HIGH);
  analogWrite(pb, 255 - speed);
  dir = direction;
  currentSpeed = speed;
}

void Motor::stop() {
  digitalWrite(p1, HIGH);
  digitalWrite(p2, HIGH);
  dir = forward;
  currentSpeed = 0;
  accelSpeed = 0.0;
  targetSpeed = 0;
}

void Motor::accel(int speed, Direction direction, int _accelSpeed) {
  targetSpeed = speed;
  accelSpeed = _accelSpeed;
  dir = direction;
}

void Motor::update() {
  if (currentSpeed <= targetSpeed) {
    currentSpeed = currentSpeed + accelSpeed;
    turn(currentSpeed, dir);
  }
  if (currentSpeed > targetSpeed) {
    currentSpeed = targetSpeed;
    turn(targetSpeed, dir);
  }
};

#endif