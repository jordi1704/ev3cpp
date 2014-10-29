/*
 * Color.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: jordi
 */

#include <Color.h>
#include "Sensor.h"
#include "stdlib.h"

Color::Color (Port_t Port, ColorMode_t Mode, DataLogger* Logger) :
							Sensor(Port,Logger)
{
  SetSensorMode(sColorMode[Mode]);
}

Color::~Color ()
{
  // TODO Auto-generated destructor stub
}

ReflectedSensor::ReflectedSensor(Port_t Port, DataLogger* Logger) :
      Color(Port, REFLECTED, Logger)
{

}

int ReflectedSensor::GetReflected()
{
  return atoi(GetSensorValue(sColorValue[REFLECTED]).c_str());
}
