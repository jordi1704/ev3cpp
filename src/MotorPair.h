/*
 * MotorPair.h
 *
 *  Created on: Oct 15, 2014
 *      Author: jordi
 */

#ifndef MOTORPAIR_H_
#define MOTORPAIR_H_

#include "Tacho.h"

class MotorPair
{
private:
Tacho* MotorL;
Tacho* MotorR;
public:
  MotorPair (Port_t LeftPort, Port_t RightPort, DataLogger* Logger=NULL);
  void Turn(float Angle, Power_t Power);
  void Pivot(Power_t Power);
  virtual
  ~MotorPair ();
};

#endif /* MOTORPAIR_H_ */
