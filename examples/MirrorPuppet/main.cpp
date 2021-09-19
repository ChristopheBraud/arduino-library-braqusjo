//
// Created by christophe on 05/09/2020.
//

/**
 * Mirror Puppet
 *
 * Mirroring the puppet position on the arm
 */
#include "Arduino.h"
#include "Braqusjo.hpp"

#define BRACCIO_VERSION 4

Braqusjo gBraqusjo;

void setup() {
  gBraqusjo.begin(BRACCIO_VERSION);
  delay(1000);
  int lAngles[6];
  gBraqusjo.getPuppetAngles(lAngles);
  gBraqusjo.move(3000, lAngles);
  Serial.begin(9600);
}

void loop() {
  int lAngles[6];
  gBraqusjo.getPuppetAngles(lAngles);
//  for(int iAngle = 0; iAngle < 6; ++iAngle) {
//    Serial.print(lAngles[iAngle]);
//    Serial.print(' ');
//  }
//  Serial.println();
  gBraqusjo.setAngles(lAngles);
}