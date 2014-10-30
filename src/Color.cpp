/*
 * Color.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: jordi
 */

#include "Color.h"
#include <iostream>

Color::Color (Port_t Port, ColorMode_t Mode, DataLogger* Logger) :
							Sensor(Port,Logger)
{
  m_DeviceID=" COLOR:"+sPortName[Port];
  SetSensorMode(sColorMode[Mode]);
}

Color::~Color ()
{
  // TODO Auto-generated destructor stub
}

LightSensor::LightSensor (Port_t Port, DataLogger* Logger) :
    Color(Port,REFLECTED,Logger)
{
}

LightSensor::~LightSensor()
{
}


int LightSensor::GetReflected()
{
  return atoi(GetSensorValue(sColorValue[REFLECTED]).c_str());
}

