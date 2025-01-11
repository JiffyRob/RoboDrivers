#ifndef ENCODERMOTORLIB
#define ENCODERMOTORLIB

#include "Arduino.h"
#include "encoder.h"
#include "motor.h"
#define KP 1.0
#define KD 0.025
#define KI 0.0

class Servo {
  public:
    Servo() {
      _motor = Motor();
      _encoder = Encoder();
      _integral = 0;
      _target = 0;
      _last_update = micros();
    }
    Servo(Encoder& encoder, Motor& motor) {
      _motor = motor;
      _encoder = encoder;
      _integral = 0;
      _target = 0;
      _last_update = micros();
    }
    void turnToAngle(int angle) {
      _target = angle;
    }
    void turnByAngle(int angle) {
      _target += angle;
    }
    int getAngle() {
      return _encoder.getAngle();
    }
    int getTarget() {
      return _target;
    }
    Motor getMotor() {
      return _motor;
    }
    Encoder getEncoder() {
      return _encoder;
    }
    void zero() {
      _encoder.zero();
    }
    void update() {
      // Algorithm shamelessly stolen from https://www.electroniclinic.com/arduino-dc-motor-speed-control-with-encoder-arduino-dc-motor-encoder/#Control_DC_motor_using_Encoder_feedback_loop
      // time delta
      unsigned long int now = micros();
      float dt = (now - _last_update) / 1e6;
      _last_update = now;
      // error
      int error = getAngle() - _target;
      // derivative
      float derivative = (error - _last_error);
      // integral
      _integral += error * dt;
      // control signal
      float signal = KP*error + KD*derivative + KI*_integral;
      // motor control
      int power = (int)fabs(signal);
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
  private:
    Encoder _encoder;
    Motor _motor;
    int _target;
    unsigned long int _last_update;
    int _last_error;
    int _integral;
};

#endif