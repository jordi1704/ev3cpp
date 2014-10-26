/*
 * Tacho.cpp
 *
 *  Created on: Oct 14, 2014
 *      Author: jordi
 */

#include "Tacho.h"
#include <iostream>

Tacho::Tacho (Port_t Port,DataLogger* Logger) : Motor(Port,Logger)
{
  cout << "Constructed Tacho motor on port " << sPortName[Port] << endl;
}

Tacho::~Tacho ()
{
}

// Override Motor::CalculateSpeed with correct conversion factor
int Tacho::CalculateSpeed(Power_t Power)
{
  return (Power*MAX_SPEED_BIG_MOTOR)/100;
}

// Shadow private Motor::SetRegulationMode since Tacho motor
// can be unregulated
void Tacho::SetRegulationMode(reg_mode_t RegMode)
{
  SetRegulationMode(RegMode);
}
