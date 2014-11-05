/*
 * Led.cpp
 *
 *  Created on: Nov 4, 2014
 *      Author: jordi
 */

#include "Led.h"

Led::Led (Port_t Port, DataLogger* Logger) : Ev3Device(Port,Logger)
{
  m_DeviceID=" LED:"+sPortName[Port];
  Trace(m_Logger,LED_DBG_LVL,m_DeviceID+FUNCT_STR);
}

Led::~Led ()
{
  Trace(m_Logger,LED_DBG_LVL,m_DeviceID+FUNCT_STR);
}




