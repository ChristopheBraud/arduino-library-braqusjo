//
// Created by christophe on 14/10/2019.
//

#ifndef BRAQUSJO_BRAQUSJO_HPP
#define BRAQUSJO_BRAQUSJO_HPP

#include "Axis.hpp"

class Braqusjo {
public:
  void setAxesOffset(int base, int shoulder, int elbow, int wristPitch, int wristRoll, int gripper);

  void setPuppetAxesOffset(int base, int shoulder, int elbow, int wristPitch, int wristRoll, int gripper);

  void begin(unsigned version);

  void end();

  void move(unsigned long duration, int angles[6]);

  void setAngles(int angles[6]);

  void getAngles(int angles[6]);

  void getPuppetAngles(int angles[6]);

protected:
  const int SOFT_START_PIN = 12;

  bool mHasSoftStart;

  Axis mAxes[6];

  int mAxesOffsets[6];

  int mPuppetAxesOffsets[6];

private:
  void softStart();

  void powerOff();

};


#endif //BRAQUSJO_BRAQUSJO_HPP
