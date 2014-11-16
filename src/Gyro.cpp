/*
 * Gyro.cpp
 *
 *  Created on: Oct 10, 2014
 *      Author: jordi
 */

#include "Gyro.h"
#include "cutils.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

/*
 * Gyro constructor
 */
Gyro::Gyro(Port_t Port, GyroMode_t Mode, DataLogger* Logger,
           int NumOfInStreams) :
    Sensor(Port,Logger,NumOfInStreams)
{
  m_DeviceID=" GYRO:"+sPortName[Port];
  SetMode(Mode);
  Trace(m_Logger,GYRO_DBG_LVL,m_DeviceID+FUNCT_STR);
}

Gyro::~Gyro()
{
  Trace(m_Logger,GYRO_DBG_LVL,m_DeviceID+FUNCT_STR);
}

/*
 * Gyro is reset by changing its mode. However in GYRO-GA mode it is not
 * possible to reset it this way.
 */
void Gyro::Reset()
{
  switch (m_GyroMode) {
    case ANGLE:
      SetMode(RATE);
      SetMode(ANGLE);
      break;
    case RATE:
      SetMode(ANGLE);
      SetMode(RATE);
    default:
      Trace(m_Logger,GYRO_DBG_LVL,m_DeviceID+ERROR_STR);
      m_Logger->~DataLogger();
      exit(1);
      break;
  }
  Trace(m_Logger,GYRO_DBG_LVL,m_DeviceID+FUNCT_STR);
}

/*
 * Set mode of Gyro
 */
void Gyro::SetMode(GyroMode_t Mode){
  SetSensorMode(sGyroMode[Mode]);
  string actualMode=GetSensorMode();
  if(sGyroMode[Mode]!=actualMode){
      Trace(m_Logger,GYRO_DBG_LVL,m_DeviceID+ERROR_STR);
      m_Logger->~DataLogger();
      exit(1);
  }
  m_GyroMode=Mode;
  Trace(m_Logger,GYRO_DBG_LVL,m_DeviceID+FUNCT_STR+actualMode);
}

GyroMode_t Gyro::GetMode(){
  string Mode=GetSensorMode();
  for(int i=0;i<GYRO_MODES;++i){
      if(Mode==sGyroMode[i]){
	  Trace(m_Logger,GYRO_DBG_LVL,m_DeviceID+FUNCT_STR+Mode);
	  return static_cast<GyroMode_t>(i);
      }
  }
  Trace(m_Logger,GYRO_DBG_LVL,m_DeviceID+ERROR_STR);
  m_Logger->~DataLogger();
  exit(1);
}

int Gyro::GetAngle(){
  if (m_GyroMode==ANGLE) {
      int Angle=atoi(GetSensorValue(sGyroValue[ANGLE_VALUE]).c_str());
      Trace(m_Logger,GYRO_DBG_LVL,m_DeviceID+FUNCT_STR+ToString(Angle));
      return Angle;
  } else {
      Trace(m_Logger,GYRO_DBG_LVL,m_DeviceID+ERROR_STR);
      m_Logger->~DataLogger();
      exit(1);
  }
}

void Gyro::GetRateAndAngle(int &Rate, int &Angle)
{
  if (m_GyroMode==ANGLE_AND_RATE) {
    Rate=atoi(GetSensorValue(sGyroValue[GA_RATE]).c_str());
    Angle=atoi(GetSensorValue(sGyroValue[GA_ANGLE]).c_str());
    Trace(m_Logger,GYRO_DBG_LVL,m_DeviceID+FUNCT_STR+
          ToString(Rate)+","+ToString(Angle));
  } else {
    Trace(m_Logger,GYRO_DBG_LVL,m_DeviceID+ERROR_STR);
    m_Logger->~DataLogger();
    exit(1);
  }
}

int Gyro::GetRate(){
  if (m_GyroMode==RATE) {
        int Rate=atoi(GetSensorValue(sGyroValue[RATE_VALUE]).c_str());
        Trace(m_Logger,GYRO_DBG_LVL,m_DeviceID+FUNCT_STR);
        return Rate;
    } else {
        Trace(m_Logger,GYRO_DBG_LVL,m_DeviceID+ERROR_STR);
        m_Logger->~DataLogger();
        exit(1);
    }
}

ServoGyro::ServoGyro(Port_t Port) : Gyro(Port,ANGLE_AND_RATE,NULL,2)
{
  m_DeviceID=" SERVO GYRO:"+sPortName[Port];
}

ServoGyro::~ServoGyro()
{

}

void ServoGyro::GetRateAndAngle(int &Rate, int &Angle)
{
  string readValue0, readValue1;

  this->m_FastInputChannels->GetData(0,readValue0);
  this->m_FastInputChannels->GetData(1,readValue1);

  Angle=atoi(readValue0.c_str());
  Rate=atoi(readValue1.c_str());
}

