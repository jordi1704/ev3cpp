/*
 * MiniTacho.h
 *
 *  Created on: Oct 12, 2014
 *      Author: jordi
 */

#ifndef MINITACHO_H_
#define MINITACHO_H_

#include "Motor.h"

class MiniTacho : public Motor
{
private:
  int CalculateSpeed(Power_t Power);
public:
  MiniTacho (Port_t Port,DataLogger* Logger=NULL);
  virtual
  ~MiniTacho ();
};

#endif /* MINITACHO_H_ */
