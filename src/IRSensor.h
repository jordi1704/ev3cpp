/*
 * IRSensor.h
 *
 *  Created on: Nov 9, 2014
 *      Author: jordi
 */

#ifndef IRSENSOR_H_
#define IRSENSOR_H_

#include <Sensor.h>

enum IRSensorMode_t {PROXIMITY, SEEKER, REMOTE, IR_MODES};
const string sIRSensorMode[IR_MODES]={"IR-PROX", "IR-SEEK", "IR-REMOTE"};

enum IRChannel_t {CH1, CH2, CH3, CH4};

class IRSensor : public Sensor
{
public:
  IRSensor (Port_t Port, IRSensorMode_t Mode, DataLogger* Logger=NULL);
  virtual
  ~IRSensor ();
  void SetIRSensorMode(IRSensorMode_t Mode);
  IRSensorMode_t m_IRSensorMode;
};

class ProximitySensor : private IRSensor
{
public:
  ProximitySensor (Port_t Port, DataLogger* Logger);
  virtual
  ~ProximitySensor();
  float GetDistance();
  void SetMaxDistance(float MaxDistance);
private:
  float m_MaxDistance;
};

class Seeker : private IRSensor
{
public:
  Seeker (Port_t Port, IRChannel_t Channel, DataLogger* Logger=NULL);
  virtual
  ~Seeker();
  int GetAngleDistance (signed char &Angle, signed char &Distance);
private:
  IRChannel_t m_Channel;
};


#endif /* IRSENSOR_H_ */
