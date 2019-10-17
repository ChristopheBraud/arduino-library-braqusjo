//
// Created by christophe on 14/10/2019.
//

#include "Braqusjo.hpp"
#include <Arduino.h>

Braqusjo::Braqusjo(unsigned pVersion) {
  mHasSoftStart = pVersion >= 4;  // SoftStart appears on shield V4
  mAxes[0].init(11, 0, 180, 90);  // Base
  mAxes[1].init(10, 15, 165, 45); // Shoulder
  mAxes[2].init(9, 0, 180, 180);  // Elbow
  mAxes[3].init(6, 0, 180, 0);    // Wrist
  mAxes[4].init(5, 0, 180, 90);   // Wrist Rotation
  mAxes[5].init(3, 10, 73, 73);   // Gripper
}

bool Braqusjo::start() {
  for(int i = 0; i < 6; ++i) {
    mAxes[i].attach();
  }
  bool lStarted = false;
  if(mHasSoftStart) {
    softStart();
    lStarted = true;
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

void Braqusjo::move(int pDuration, int *pAngles) {
  unsigned long lStart = millis();
  int lStartAngles[6];
  for(int iAxis = 0; iAxis < 6; ++iAxis) {
    lStartAngles[iAxis] = mAxes[iAxis].getAngle();
  }
  int lAngles[6];
  while(millis() - lStart < pDuration) {
    for(int iAxis = 0; iAxis < 6; ++iAxis) {
      lAngles[iAxis] = map(millis() - lStart, 0, pDuration, lStartAngles[iAxis], pAngles[iAxis]);
    }
    setAngles((lAngles));
    delay(1);
  }
  setAngles(pAngles);
}

void Braqusjo::setAngles(int *pAngles) {
  for(int iAxis = 0; iAxis < 6; ++iAxis) {
    mAxes[iAxis].setAngle(pAngles[iAxis]);
  }
}

void Braqusjo::softStart() {
  unsigned long lStartTime = millis();
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