/*
 * IRSensor.cpp
 *
 *  Created on: Nov 9, 2014
 *      Author: jordi
 */

#include "IRSensor.h"
#include "cutils.h"

IRSensor::IRSensor (Port_t Port, IRSensorMode_t Mode, DataLogger* Logger) :
  Sensor(Port, Logger)
{
  m_DeviceID=" IR_SENSOR:"+sPortName[Port];
  m_IRSensorMode=Mode;
  IRSensor::SetIRSensorMode(Mode);
  Trace(m_Logger,IRSENSOR_DBG_LVL,m_DeviceID+FUNCT_STR);
}

IRSensor::~IRSensor ()
{
  Trace(m_Logger,IRSENSOR_DBG_LVL,m_DeviceID+FUNCT_STR);
}

void IRSensor::SetIRSensorMode(IRSensorMode_t Mode)
{
  Sensor::SetSensorMode(sIRSensorMode[Mode]);
  m_IRSensorMode=Mode;
  Trace(m_Logger,IRSENSOR_DBG_LVL,m_DeviceID+FUNCT_STR+sIRSensorMode[Mode]);
}

ProximitySensor::ProximitySensor(Port_t Port, DataLogger* Logger) :
    IRSensor(Port,PROXIMITY,Logger)
{
  m_DeviceID=" PROXIMITY_SENSOR:"+sPortName[Port];
  Trace(m_Logger,PROXIMITY_DBG_LVL,m_DeviceID+FUNCT_STR);
}

ProximitySensor::~ProximitySensor()
{
  Trace(m_Logger,PROXIMITY_DBG_LVL,m_DeviceID+FUNCT_STR);
}

void ProximitySensor::SetMaxDistance(float MaxDistance)
{
  m_MaxDistance=MaxDistance;
  Trace(m_Logger,PROXIMITY_DBG_LVL,m_DeviceID+FUNCT_STR+ToString(MaxDistance));
}

/*
 * Returns distance to object, from 0 to m_MaxDistance. Typically, maximum
 * detectable distance is 70cm. Thus, setting MaxDistance to 70cm (default),
 * will return any distance value between 0 and 70cm. After calibration,
 * MaxDistance may be set to a different value
 */
float ProximitySensor::GetDistance()
{
  float fDistance;
  string sDistance=Sensor::GetSensorValue("value0");
  fDistance=m_MaxDistance*atoi(sDistance.c_str())/100.f;
  Trace(m_Logger,PROXIMITY_DBG_LVL,m_DeviceID+FUNCT_STR+ToString(fDistance));
  return fDistance;
}
