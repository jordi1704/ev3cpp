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
  m_RxChannel=CH1;
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
  m_MaxDistance=70.0f;
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

Seeker::Seeker(Port_t Port, IRChannel_t Channel, DataLogger* Logger) :
    IRSensor(Port, SEEKER, Logger)
{
  m_DeviceID=" SEEKER:"+sPortName[Port];
  m_RxChannel=Channel;
  Trace(m_Logger,SEEKER_DBG_LVL,m_DeviceID+FUNCT_STR);
}

Seeker::~Seeker()
{
  Trace(m_Logger,SEEKER_DBG_LVL,m_DeviceID+FUNCT_STR);
}

int Seeker::GetAngleDistance(signed char &Angle, signed char &Distance)
{
  string sAngle="value"+ToString(m_RxChannel);
  string sDistance="value"+ToString(m_RxChannel+1);
  Angle=atoi(GetSensorValue(sAngle).c_str());
  Distance=atoi(GetSensorValue(sDistance).c_str());
  Trace(m_Logger,SEEKER_DBG_LVL,m_DeviceID+FUNCT_STR+sAngle+","+sDistance);
  // Return 0 when no beacon is present
  return ((Angle==0) && (Distance=0-128)) ? 0 : 1;
}

Remote::Remote(Port_t Port, IRChannel_t Channel, DataLogger* Logger) :
    IRSensor(Port, REMOTE, Logger)
{
  m_DeviceID=" REMOTE:"+sPortName[Port];
  m_RxChannel=Channel;
  Trace(m_Logger,REMOTE_DBG_LVL,m_DeviceID+FUNCT_STR);
}

Remote::~Remote()
{
  Trace(m_Logger,REMOTE_DBG_LVL,m_DeviceID+FUNCT_STR);
}

Button_t Remote::GetButton()
{
  string button = GetSensorValue("value"+ToString(m_RxChannel));
  Trace(m_Logger,REMOTE_DBG_LVL,m_DeviceID+FUNCT_STR+button);
  return static_cast<Button_t>(atoi(button.c_str()));
}

