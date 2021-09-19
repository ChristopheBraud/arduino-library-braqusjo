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
  mDefaultAngle = constrain(pDefaultAngle, mMinAngle, mMaxAngle);
}

void Axis::attach() {
  mServo.attach(mPin);
  setAngle(mDefaultAngle);
}

void Axis::detach() {
  mServo.detach();
}

void Axis::setOffset(int pOffset) {
  mOffset = pOffset;
}

int Axis::setAngle(int pAngle) {
  int lAngle = constrain(pAngle + mOffset, mMinAngle, mMaxAngle);
  mAngle = constrain(map(lAngle, 0, 180, 500, 2500), 500, 2500);
  mServo.writeMicroseconds(mAngle);
  return lAngle;
}

int Axis::getAngle() {
  return map(mAngle, 500, 2500, 0, 180);
}
