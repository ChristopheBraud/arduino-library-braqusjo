//
// Created by christophe on 14/10/2019.
//

#ifndef BRAQUSJO_BRAQUSJO_HPP
#define BRAQUSJO_BRAQUSJO_HPP

#include "Axis.hpp"

class Braqusjo {
public:
  Braqusjo(unsigned pVersion);

  bool start();

  bool stop();

  void move(int pDuration, int pAngles[6]);

  void setAngles(int pAngles[6]);

protected:
  const int SOFT_START_PIN = 12;

  bool mHasSoftStart;

  Axis mAxes[6];

private:
  void softStart();

  void powerOff();

};


#endif //BRAQUSJO_BRAQUSJO_HPP
