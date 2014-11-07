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
public:
  MotorPair (Port_t LeftPort, Port_t RightPort, DataLogger* Logger=NULL);
  virtual
  ~MotorPair ();
  void Turn(float Angle, Power_t Power);
  void Pivot(Power_t Power);
  void Straight(Power_t Power);
private:
  Tacho* MotorL;
  Tacho* MotorR;
  string m_DeviceID;
  DataLogger* m_Logger;
};

#endif /* MOTORPAIR_H_ */
