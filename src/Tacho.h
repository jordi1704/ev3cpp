/*
 * Tacho.h
 *
 *  Created on: Oct 14, 2014
 *      Author: jordi
 */

#ifndef TACHO_H_
#define TACHO_H_

#include "Motor.h"

class Tacho : public Motor
{
private:
  int CalculateSpeed(Power_t Power);
public:
  void SetRegulationMode(reg_mode_t RegMode);
  Tacho (Port_t Port,DataLogger* Logger=NULL);
  virtual
  ~Tacho ();
};

#endif /* TACHO_H_ */
