//
// Created by christophe on 16/10/2019.
//

#include "Axis.hpp"

Axis::Axis() {

}

void Axis::init(unsigned pPin, int pMinAngle, int pMaxAngle, int pDefaultAngle) {
  mPin = pPin;
  mMinAngle = pMinAngle;
  mMaxAngle = pMaxAngle;
  mDefaultAngle = max(mMinAngle, min(mMaxAngle, pDefaultAngle));
}

void Axis::attach() {
  mServo.attach(mPin);
  setAngle(mDefaultAngle);
}

void  Axis::detach() {
  mServo.detach();
}

int Axis::setAngle(int pAngle) {
  int lAngle = max(mMinAngle, min(mMaxAngle, pAngle));
  mAngle = map(lAngle, 0, 180, 500, 2500);
  mServo.writeMicroseconds(mAngle);
  return lAngle;
}

int Axis::getAngle() {
  return map(mAngle, 500, 2500, 0, 180);
}
