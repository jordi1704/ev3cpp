/*
 * MiniTacho.cpp
 *
 *  Created on: Oct 12, 2014
 *      Author: jordi
 */

#include "MiniTacho.h"
#include <iostream>
#include "cutils.h"


MiniTacho::MiniTacho(Port_t Port,DataLogger* Logger) : Motor(Port,Logger)
{
  m_DeviceID=" MINITACHO:"+sPortName[Port];
  Trace(m_Logger,MINITACHO_DBG_LVL,m_DeviceID+FUNCT_STR);
}


MiniTacho::~MiniTacho ()
{
  Trace(m_Logger,MINITACHO_DBG_LVL,m_DeviceID+FUNCT_STR);
}

int MiniTacho::CalculateSpeed(Power_t Power){
  return (Power*MAX_SPEED_SMALL_MOTOR)/100;
}



