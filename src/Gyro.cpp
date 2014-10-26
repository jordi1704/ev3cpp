/*
 * Gyro.cpp
 *
 *  Created on: Oct 10, 2014
 *      Author: jordi
 */

#include "Gyro.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

void Gyro::Reset()
{
  switch (GetMode()) {
    case ANGLE:
      SetMode(RATE);
      SetMode(ANGLE);
      break;
    case RATE:
      SetMode(ANGLE);
      SetMode(RATE);
    default:
      cout << "Unable to reset Gyro. Unknown initial mode" << endl;
      exit(1);
      break;
  }
}

void Gyro::SetMode(GyroMode_t Mode){
  SetSensorMode(sGyroMode[Mode]);
  string actualMode=GetSensorMode();
  if(sGyroMode[Mode]!=actualMode){
      cout << "Gyro Mode: " << sGyroMode[Mode] << " could not be set" << endl;
      cout << "Current Mode : " << actualMode << endl;
      exit(1);
  }
  m_GyroMode=Mode;
}

GyroMode_t Gyro::GetMode(){
  string Mode=GetSensorMode();
  for(int i=0;i<_GYRO_MODES_;++i){
      if(Mode==sGyroMode[i]) return static_cast<GyroMode_t>(i);
  }
  cout << "Unknown Gyro Mode" << endl;
  exit(1);
}

int Gyro::GetAngle(){
  //string actualMode=GetSensorMode();
  if (m_GyroMode==ANGLE) {
      return atoi(GetSensorValue(sGyroValue[ANGLE_VALUE]).c_str());
  } else {
      cout << "Unable to get Gyro becasue not in GYRO-ANG mode " << endl;
      exit(1);
  }
}

void Gyro::GetRateAndAngle(int &Rate, int &Angle)
{
  if (m_GyroMode==ANGLE_AND_RATE) {
    Rate=atoi(GetSensorValue(sGyroValue[GA_RATE]).c_str());
    Angle=atoi(GetSensorValue(sGyroValue[GA_ANGLE]).c_str());
  } else {
    cout << "Unable to get angle/rate because not in GYRO-G&A mode" << endl;
    exit(1);
  }
}

int Gyro::GetRate(){
  if (m_GyroMode==RATE) {
        return atoi(GetSensorValue(sGyroValue[RATE_VALUE]).c_str());
    } else {
        cout << "Unable to get Gyro becasue not in RATE mode " << endl;
        exit(1);
    }
}

Gyro::Gyro(Port_t Port, GyroMode_t Mode, DataLogger* Logger) :
    Sensor(Port,Logger)
{
  SetMode(Mode);
}
