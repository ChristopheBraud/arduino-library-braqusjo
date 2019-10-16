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
  mDefaultAngle = pDefaultAngle;
}

void Axis::attach() {
  mServo.attach(mPin);
  mServo.writeMicroseconds(map(mDefaultAngle, 0, 180, 500, 2500));
}

void  Axis::detach() {
  mServo.detach();
}
