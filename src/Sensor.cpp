/*
 * Sensor.cpp
 *
 *  Created on: Oct 10, 2014
 *      Author: jordi
 */

#include "Sensor.h"
#include "cutils.h"

Sensor::Sensor (Port_t Port, DataLogger* Logger, int NumOfFastInputChannels)
  : Ev3Device(Port,Logger)
{
  m_DeviceID=" SENSOR:"+sPortName[Port];
  if(NumOfFastInputChannels){
      m_FastInputChannels=new InputStreams(NumOfFastInputChannels,
                                           this->GetDevicePath());
  }
  m_NumOfFastInputChannels=NumOfFastInputChannels;
  Trace(m_Logger,SENSOR_DBG_LVL,m_DeviceID+FUNCT_STR);
}

Sensor::~Sensor ()
{
  delete m_FastInputChannels;
  Trace(m_Logger,SENSOR_DBG_LVL,m_DeviceID+FUNCT_STR);
}

void Sensor::SetSensorMode (string Mode)
{
  SetDeviceParameter(MODE,Mode);
  Trace(m_Logger,SENSOR_DBG_LVL,m_DeviceID+FUNCT_STR+Mode);
}

string Sensor::GetSensorMode()
{
  string Mode=GetDeviceParameter(MODE);
  Trace(m_Logger,SENSOR_DBG_LVL,m_DeviceID+FUNCT_STR+Mode);
  return Mode;
}

string Sensor::GetSensorValue(string Value)
{
  string SensorValue=GetDeviceParameter(Value);
  Trace(m_Logger,SENSOR_DBG_LVL,m_DeviceID+FUNCT_STR+Value+","+SensorValue);
  return SensorValue;
}


