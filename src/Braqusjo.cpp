//
// Created by christophe on 14/10/2019.
//

#include <Arduino.h>
#include "Braqusjo.hpp"

void Braqusjo::setAxesOffset(int base, int shoulder, int elbow, int wristPitch, int wristRoll, int gripper) {
  mAxes[0].setOffset(base);
  mAxes[1].setOffset(shoulder);
  mAxes[2].setOffset(elbow);
  mAxes[3].setOffset(wristPitch);
  mAxes[4].setOffset(wristRoll);
  mAxes[5].setOffset(gripper);
}

void Braqusjo::setPuppetAxesOffset(int base, int shoulder, int elbow, int wristPitch, int wristRoll, int gripper) {
  mPuppetAxesOffsets[0] = base;
  mPuppetAxesOffsets[1] = shoulder;
  mPuppetAxesOffsets[2] = elbow;
  mPuppetAxesOffsets[3] = wristPitch;
  mPuppetAxesOffsets[4] = wristRoll;
  mPuppetAxesOffsets[5] = gripper;
}

void Braqusjo::begin(unsigned version) {
  mHasSoftStart = version >= 4;  // SoftStart appears on shield V4
  mAxes[0].init(11, 0, 180, 90);  // Base
  mAxes[1].init(10, 15, 165, 45); // Shoulder
  mAxes[2].init(9, 0, 180, 180);  // Elbow
  mAxes[3].init(6, 0, 180, 0);    // Wrist Pitch
  mAxes[4].init(5, 0, 180, 90);   // Wrist Roll
  mAxes[5].init(3, 10, 73, 73);   // Gripper
  for(int iAxis = 0; iAxis < 6; ++iAxis) {
    mAxes[iAxis].attach();
  }
  softStart();
}

void Braqusjo::end() {
  powerOff();
  for(int i = 0; i < 6; ++i) {
    mAxes[i].detach();
  }
}

void Braqusjo::move(unsigned long duration, int *angles) {
  unsigned long lStart = millis();
  int lStartAngles[6];
  for(int iAxis = 0; iAxis < 6; ++iAxis) {
    lStartAngles[iAxis] = mAxes[iAxis].getAngle();
  }
  int lAngles[6];
  while(millis() - lStart < duration) {
    for(int iAxis = 0; iAxis < 6; ++iAxis) {
      lAngles[iAxis] = map(millis() - lStart, 0, duration, lStartAngles[iAxis], angles[iAxis]);
    }
    setAngles((lAngles));
    delay(1);
  }
  setAngles(angles);
}

void Braqusjo::setAngles(int *angles) {
  for(int iAxis = 0; iAxis < 6; ++iAxis) {
    mAxes[iAxis].setAngle(angles[iAxis]);
  }
}

void Braqusjo::getAngles(int *angles) {
  for(int iAxis = 0; iAxis < 6; ++iAxis) {
    angles[iAxis] = mAxes[iAxis].getAngle();
  }
}

void Braqusjo::getPuppetAngles(int *angles) {
  uint8_t lPorts[6] = {A0, A1, A2, A3, A4, A5};
  for(int iAngle = 0; iAngle < 6; ++iAngle) {
    Serial.print(analogRead(lPorts[iAngle]) + mPuppetAxesOffsets[iAngle] - 512);
    Serial.print(' ');
  }
  Serial.println();
  angles[0] = constrain(map(analogRead(A0) + mPuppetAxesOffsets[0], 170, 854, 0, 180), 0, 180);
  angles[1] = constrain(map(analogRead(A1) + mPuppetAxesOffsets[1], 170, 854, 0, 180), 0, 180);
  angles[2] = constrain(map(analogRead(A2) + mPuppetAxesOffsets[2], 170, 854, 180, 0), 0, 180);
  angles[3] = constrain(map(analogRead(A3) + mPuppetAxesOffsets[3], 170, 854, 0, 180), 0, 180);
  angles[4] = constrain(map(analogRead(A4) + mPuppetAxesOffsets[4], 227, 797, 15, 165), 15, 165);
  angles[5] = constrain(map(analogRead(A5) + mPuppetAxesOffsets[5], 0, 1024, 10, 73), 10, 73);
}

void Braqusjo::softStart() {
  if(mHasSoftStart) {
    unsigned long lStartTime = millis();
    while(millis() - lStartTime < 2000) {
      delayMicroseconds(80);
      digitalWrite(SOFT_START_PIN, LOW);
      delayMicroseconds(530 - 80);
      digitalWrite(SOFT_START_PIN, HIGH);
    }
  }
}

void Braqusjo::powerOff() {
  if(mHasSoftStart) {
    digitalWrite(SOFT_START_PIN, LOW);
  }
}
