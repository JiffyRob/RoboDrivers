#ifndef ENCODERLIB
#define ENCODERLIB

#define ENCODER_TOLERANCE 200
#define EPIN_LOW 0
#define EPIN_HIGH 1
#define EPIN_UNDEF 2

class Encoder {
  public:
    Encoder() {
      _pinA = 0;
      _pinB = 0;
      _pinM = 0;
      _ticks = 0;
      _net = 0;
      _stateA = EPIN_UNDEF;
      _stateB = EPIN_UNDEF;
    }
    Encoder(int pinA, int pinB, int pinM, int initialPos) {
      _pinA = pinA;
      _pinB = pinB;
      _pinM = pinM;
      _ticks = initialPos;
      _net = 0;
      _stateA = EPIN_UNDEF;
      _stateB = EPIN_UNDEF;
    }
    int getAngle() {
      return _ticks % 1000;
    }
    int getRotations() {
      return _ticks / 1000;
    }
    long int getCumulative() {
      return _ticks;
    }
    void zero() {
      _ticks = 0;
      _stateA = getState(_pinA);
      _stateB = getState(_pinB);
    }
    int getPinA() {
      return _pinA;
    }
    int getPinB() {
      return _pinB;
    }
    void onChangeA() {
      if (getState(_pinA) == EPIN_HIGH) {
        _stateA = EPIN_HIGH;
        inc(!_stateB);
      } else {
        _stateA = EPIN_LOW;
        inc(_stateB);
      }
    }
    void onChangeB() {
      if (getState(_pinB) == EPIN_HIGH) {
        _stateB = EPIN_HIGH;
        inc(_stateA);
      } else {
        _stateB = EPIN_LOW;
        inc(!_stateA);
      }
    }
    void update() {
      _net = 0;
    }
  private:
    int _pinA;
    int _pinB;
    int _pinM;
    volatile int _stateB;
    volatile int _stateA;
    volatile int _ticks;
    volatile int _net;
    int getState(int pin) {
      int valueP = digitalRead(pin);
      if (valueP) {
        return EPIN_HIGH;
      }
      return EPIN_LOW;
    }
    void inc(bool isForward) {
      if (isForward) {
        _ticks ++;
        _net++;
      } else {
        _ticks--;
        _net--;
      }
    }
};

#endif