/*
 * Sensor.h
 *
 *  Created on: Oct 10, 2014
 *      Author: jordi
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include "Ev3Device.h"
#include "DirectIO.h"

#define MODE "mode"

using namespace std;

class Sensor : public Ev3Device
{
public:
  Sensor(Port_t, DataLogger* Logger=NULL, int NumOfFastInputChannels=0);
  virtual ~Sensor ();
  void SetSensorMode(string Mode);
  string GetSensorMode();
  string GetSensorValue(string Value);
  int m_NumOfFastInputChannels;
  InputStreams* m_FastInputChannels;
};

#endif /* SENSOR_H_ */
