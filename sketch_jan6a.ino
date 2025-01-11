#include "encoder.h"
#include "motor.h"
#include "encoderMotor.h"
#define RED 27
#define WHITE 26
#define YELLOW 25
#define MP1 12
#define MP2 12

Encoder e = Encoder(RED, WHITE, YELLOW, 0);
Motor m = Motor(MP1, MP2);
Servo s = Servo(e, m);

void onA_e() {
  e.onChangeA();
}
void onB_e() {
  e.onChangeB();
}

void setup() {
  // Set pin mode
  pinMode(RED, INPUT);
  pinMode(WHITE, INPUT);
  pinMode(YELLOW, INPUT);
  pinMode(MP1, OUTPUT);
  pinMode(MP2, OUTPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(e.getPinA()), onA_e, CHANGE);
  attachInterrupt(digitalPinToInterrupt(e.getPinB()), onB_e, CHANGE);
  s.zero();
  s.turnToAngle(250);
}

void loop() {
  e.update();
  Serial.println(e.getCumulative());
}