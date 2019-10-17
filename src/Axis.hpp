//
// Created by christophe on 16/10/2019.
//

#ifndef BRAQUSJO_AXIS_HPP
#define BRAQUSJO_AXIS_HPP

#include <Arduino.h>
#include <Servo.h>

class Axis {
public:
  Axis();

  void init(unsigned pPin, int pMinAngle, int pMaxAngle, int pDefaultAngle);

  void attach();

  void detach();

  int setAngle(int pAngle);

  int getAngle();

protected:
  unsigned mPin;
  int mOffset;
  int mAngle;
  int mMinAngle;
  int mMaxAngle;
  int mDefaultAngle;
  Servo mServo;
};


#endif //BRAQUSJO_AXIS_HPP
