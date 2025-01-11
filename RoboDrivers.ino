#define M1A 3
#define M1B 2
#define M2A 5
#define M2B 4
#define E1 24
#define E2 25
#define ULTRASONIC_PIN 54
#define SPEED 255
#include "motor.h"
#include "ultrasonic.h"
#include "encoder.h"
#include "encoderMotor.h"
#include <math.h>

Motor m1 = Motor(M1A, M1B);
Motor m2 = Motor(M2A, M2B);
Encoder e1 = Encoder(E1, E2);
Servo s = Servo();
UltrasonicSensor s1 = UltrasonicSensor();

void e1_changea() {
  e1.onChangeA();
  s.onEncoderTick();
}

void e2_changeb() {
  e1.onChangeB();
  s.onEncoderTick();
}

void setup() {
  s.setEncoder(&e1);
  s.setMotor(m2);
  Serial.begin(9600);
  s1.setPin(ULTRASONIC_PIN);
  Serial.println("Hi there!");
  attachInterrupt(digitalPinToInterrupt(e1.getPinA()), e1_changea, CHANGE);
  attachInterrupt(digitalPinToInterrupt(e1.getPinB()), e2_changeb, CHANGE);
  s.turnByAngle(500);
}

void go_forward() {
  m1.turn(SPEED, forward);
  m2.turn(SPEED, forward);
}

void go_turn() {
  m1.turn(SPEED, forward);
  m2.turn(SPEED, backward);
}

void stop() {
  m1.stop();
  m2.stop();
}

void loop() {
  s.update();
  s1.update();
  double dist = s1.distance();
  // s.turnToAngle(5000);
}
