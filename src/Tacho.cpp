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
  m_DeviceID=" TACHO:"+sPortName[Port];
  Trace(m_Logger,TACHO_DBG_LVL,m_DeviceID+"-> Constructed Tacho");
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
