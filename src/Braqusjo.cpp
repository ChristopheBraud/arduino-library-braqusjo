//
// Created by christophe on 14/10/2019.
//

#include "Braqusjo.hpp"

Braqusjo::Braqusjo(unsigned pVersion) {
  mHasSoftStart = pVersion >= 4; // SoftStart appears on shield V4
}

bool Braqusjo::start() {
  bool lStarted = false;
  if(mHasSoftStart) {
    softStart();
    lStrated = true;
  }
  return lStarted;
}

bool Braqusjo::stop() {
  bool lStopped  = false;
  if(mHasSoftStart) {
    powerOff();
    lStopped = true;
  }
  return lStopped;
}

void Braqusjo::softStart() {
  while(millis() - lStartTime < 2000) {
    delayMicroseconds(80);
    digitalWrite(SOFT_START_PIN, LOW);
    delayMicroseconds(530 - 80);
    digitalWrite(SOFT_START_PIN, HIGH);
  }
}

void Braqusjo::powerOff() {
  digitalWrite(SOFT_START_PIN, LOW);
}