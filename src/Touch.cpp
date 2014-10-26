/*
 * Touch.cpp
 *
 *  Created on: Oct 5, 2014
 *      Author: jordi
 */

#include "Touch.h"

Touch::Touch(Port_t Port, DataLogger* Logger) : Sensor(Port,Logger)
{
}

Touch::~Touch ()
{
}

bool Touch::IsPressed(){
  return (GetSensorValue(TOUCH_STATE)==TOUCH_PRESSED);
}
