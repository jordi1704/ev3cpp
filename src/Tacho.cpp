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
  Trace(m_Logger,TACHO_DBG_LVL,m_DeviceID+FUNCT_STR);
}

Tacho::~Tacho ()
{
  Trace(m_Logger,TACHO_DBG_LVL,m_DeviceID+FUNCT_STR);
}

// Override Motor::CalculateSpeed with correct conversion factor
int Tacho::CalculateSpeed(Power_t Power)
{
  return (Power*MAX_SPEED_BIG_MOTOR)/100;
}

// Allow to set regulation mode for Tacho motor, unlike minitacho which is,
// always, regulated
void Tacho::SetRegulationMode(reg_mode_t RegMode)
{
  Motor::SetRegulationMode(RegMode);
}
