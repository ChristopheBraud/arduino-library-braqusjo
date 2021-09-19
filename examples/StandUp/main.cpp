//
// Created by christophe on 05/09/2020.
//

/**
 * Stand Up
 *
 * Set the arm straight to the sky
 */
#include "Arduino.h"
#include "Braqusjo.hpp"

#define BRACCIO_VERSION 4

Braqusjo gBraqusjo;

void setup() {
  gBraqusjo.begin(BRACCIO_VERSION);
  int lAngles[6] = {90, 90, 90, 90, 90, 45};
  gBraqusjo.move(1000, lAngles);
}

void loop() {

}