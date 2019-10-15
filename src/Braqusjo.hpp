//
// Created by christophe on 14/10/2019.
//

#ifndef BRAQUSJO_BRAQUSJO_HPP
#define BRAQUSJO_BRAQUSJO_HPP

class Braqusjo {
public:
  Braqusjo(unsigned pVersion) explicit;

  bool start();

  bool stop();

protected:
  const int SOFT_START_PIN = 12;

  bool mHasSoftStart;

private:
  void softStart();

  void powerOff();

};


#endif //BRAQUSJO_BRAQUSJO_HPP
