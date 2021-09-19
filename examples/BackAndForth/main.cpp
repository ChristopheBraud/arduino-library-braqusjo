//
// Created by christophe on 05/09/2020.
//

/**
 * Back And Forth
 *
 * Animation loop between two extreme position
 */
#include "Arduino.h"
#include "Braqusjo.hpp"

#define BRACCIO_VERSION 4

Braqusjo gBraqusjo;

void setup() {
  gBraqusjo.begin(BRACCIO_VERSION);
  int lAngles[6] = {90, 45, 180, 0, 90, 73};
  gBraqusjo.move(1000, lAngles);
}

void loop() {
  int lAnglesA[6] = {0, 45, 180, 0, 0, 73};
  int lAnglesB[6] = {180, 135, 0, 180, 180, 10};
  gBraqusjo.move(3000, lAnglesA);
  delay(1000);
  gBraqusjo.move(3000, lAnglesB);
  delay(1000);
}