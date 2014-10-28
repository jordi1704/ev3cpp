/*
 * Touch.cpp
 *
 *  Created on: Oct 5, 2014
 *      Author: jordi
 */

#include "Touch.h"

Touch::Touch(Port_t Port, DataLogger* Logger) : Sensor(Port,Logger)
{
  m_DeviceID=" TOUCH:"+sPortName[Port];
  Trace(m_Logger,TOUCH_DBG_LVL,m_DeviceID+"-> Constructed Touch");
}

Touch::~Touch ()
{
}

bool Touch::IsPressed(){
  bool isPressed=GetSensorValue(TOUCH_STATE)==TOUCH_PRESSED;
  if (isPressed) {
      Trace(m_Logger,TOUCH_DBG_LVL,m_DeviceID+"-> Pressed");
  } else {
      Trace(m_Logger,TOUCH_DBG_LVL,m_DeviceID+"-> Released");
  }
  return (isPressed);
}
