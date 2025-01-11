#ifndef ENCODERMOTORLIB
#define ENCODERMOTORLIB

#include "Arduino.h"
#include "encoder.h"
#include "motor.h"
#define KP 2.1
#define KD 0.2
#define KI 0

class Servo {
  public:
    Servo() {
      _integral = 0;
      _target = 0;
      _last_update = micros();
    }
    void setEncoder(Encoder *encoder) {
      _encoder = encoder;
    }
    void setMotor(Motor motor) {
      _motor = motor;
    }
    void turnToAngle(int angle) {
      _target = angle;
      _integral = 0;
    }
    void turnByAngle(int angle) {
      _target += angle;
      _integral = 0;
    }
    int getAngle() {
      return _encoder->getAngle();
    }
    int getTarget() {
      return _target;
    }
    void zero() {
      _encoder->zero();
    }
    void tick() {
      // Algorithm shamelessly stolen from https://www.electroniclinic.com/arduino-dc-motor-speed-control-with-encoder-arduino-dc-motor-encoder/#Control_DC_motor_using_Encoder_feedback_loop
      // time delta
      unsigned long int now = micros();
      float dt = (now - _last_update) / 1e6;
      _last_update = now;
      // error
      int error = _target - _encoder->getCumulative();
      // derivative
      float derivative = (error - _last_error);
      // integral
      _integral += error * dt;
      // control signal
      float signal = KP*error + KD*derivative + KI*_integral;
      // motor control
      int power = min(250, (int)fabs(signal));
      Direction dir;
      if (signal >= 0) {
        dir = forward;
      } else {
        dir = backward;
      }
      _motor.turn(power, dir);
      // record error
      _last_error = error;
    }
  void onEncoderTick() {
    tick();
  }
  void update() {
    Serial.println((_target - _encoder->getCumulative()) * 360.0 / 2000.0);
    tick();
  }
  private:
    Encoder* _encoder;
    Motor _motor;
    int _target;
    unsigned long int _last_update;
    int _last_error;
    int _integral;
};

#endif