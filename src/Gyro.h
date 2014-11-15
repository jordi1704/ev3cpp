/*
 * Gyro.h
 *
 *  Created on: Oct 10, 2014
 *      Author: jordi
 */

#ifndef GYRO_H_
#define GYRO_H_

#include "Sensor.h"

enum GyroMode_t {ANGLE, RATE, ANGLE_AND_RATE, GYRO_MODES};
const string sGyroMode[GYRO_MODES+1]={"GYRO-ANG","GYRO-RATE",
                                        "GYRO-G&A","mode"};

enum GyroValue_t {ANGLE_VALUE, RATE_VALUE, GA_ANGLE, GA_RATE, GYRO_VALUES};
const string sGyroValue[GYRO_VALUES]={"value0","value0","value0","value1"};

class Gyro : public Sensor
{
private:
  GyroMode_t m_GyroMode;
public:
  void Reset();
  int GetAngle();
  int GetRate();
  void SetMode(GyroMode_t Mode);
  void GetRateAndAngle(int &Rate, int &Angle);
  GyroMode_t GetMode();
  Gyro (Port_t Port, GyroMode_t Mode, DataLogger* Logger=NULL,
        int NumOfInStreams=0);
  virtual
  ~Gyro ();
};

class ServoGyro : private Gyro
{
public:
  ServoGyro(Port_t Port);
  virtual ~ServoGyro();
  void GetRateAndAngle(int &Rate, int &Angle);
};



#endif /* GYRO_H_ */
