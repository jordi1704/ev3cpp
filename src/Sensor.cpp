/*
 * Sensor.cpp
 *
 *  Created on: Oct 10, 2014
 *      Author: jordi
 */

#include "Sensor.h"
#include "cutils.h"

Sensor::Sensor (Port_t Port, DataLogger* Logger, int NumOfInStreams)
  : Ev3Device(Port,Logger)
{
  m_InStreams=new dirIO::DirectIO*[NumOfInStreams];
  m_DeviceID=" SENSOR:"+sPortName[Port];
  for (int i = 0; i < NumOfInStreams; ++i) {
    string st=this->Ev3Device::GetDevicePath()+"/value"+ToString(i);
    m_InStreams[i]=new dirIO::DirectIO(dirIO::IN,st);
  }
  m_NumOfInStreams=NumOfInStreams;
  Trace(m_Logger,SENSOR_DBG_LVL,m_DeviceID+FUNCT_STR);
}

Sensor::~Sensor ()
{
  for (int i = 0; i < m_NumOfInStreams; ++i) {
    delete m_InStreams[i];
  }
  delete [] m_InStreams;
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


