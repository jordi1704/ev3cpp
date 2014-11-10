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

enum Button_t {NONE, RED_UP, RED_DN, BLUE_UP, BLUE_DN, RED_UP_BLUE_UP,
  RED_UP_BLUE_DN, RED_DN_BLUE_UP, RED_DN_BLUE_DN, BEACON_ON, RED_UP_RED_DN,
  BLUE_UP_BLUE_DN};

class IRSensor : public Sensor
{
public:
  IRSensor (Port_t Port, IRSensorMode_t Mode, DataLogger* Logger=NULL);
  virtual
  ~IRSensor ();
  void SetIRSensorMode(IRSensorMode_t Mode);
protected:
  IRSensorMode_t m_IRSensorMode;
  IRChannel_t m_RxChannel;
};

class ProximitySensor : private IRSensor
{
public:
  ProximitySensor (Port_t Port, DataLogger* Logger=NULL);
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
};

class Remote : private IRSensor
{
public:
  Remote (Port_t Port, IRChannel_t Channel, DataLogger* Logger=NULL);
  virtual
  ~Remote();
  Button_t GetButton();
};


#endif /* IRSENSOR_H_ */
