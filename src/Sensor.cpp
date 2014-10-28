/*
 * Sensor.cpp
 *
 *  Created on: Oct 10, 2014
 *      Author: jordi
 */

#include "Sensor.h"

Sensor::Sensor (Port_t Port, DataLogger* Logger) : Ev3Device(Port,Logger)
{
  m_DeviceID=" SENSOR:"+sPortName[Port];
  Trace(m_Logger,SENSOR_DBG_LVL,m_DeviceID+"-> Constructed Sensor");
}

Sensor::~Sensor ()
{
  Trace(m_Logger,SENSOR_DBG_LVL,m_DeviceID+"-> Sensor destroyed");
}

void Sensor::SetSensorMode (string Mode)
{
  SetDeviceParameter(MODE,Mode);
  Trace(m_Logger,SENSOR_DBG_LVL,m_DeviceID+"-> SetSensorMode: "+Mode);
}

string Sensor::GetSensorMode()
{
  string Mode=GetDeviceParameter(MODE);
  Trace(m_Logger,SENSOR_DBG_LVL,m_DeviceID+"-> GetSensorMode: "+Mode);
  return Mode;
}

string Sensor::GetSensorValue(string Value)
{
  string SensorValue=GetDeviceParameter(Value);
  Trace(m_Logger,SENSOR_DBG_LVL,m_DeviceID+"-> GetSensorValue: "+
        Value+"  value: "+SensorValue);
  return SensorValue;
}


