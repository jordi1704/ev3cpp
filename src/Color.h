/*
 * Color.h
 *
 *  Created on: Oct 23, 2014
 *      Author: jordi
 */

#ifndef COLOR_H_
#define COLOR_H_

#include "Sensor.h"

enum ColorMode_t {REFLECTED, AMBIENT, _COLOR_MODES_};
const string sColorMode[_COLOR_MODES_+1]={"COL-REFLECT","COL-AMBIENT","mode"};
const string sColorValue[_COLOR_MODES_]={"value0","value0"};

class Color : public Sensor
{
public:
  Color (Port_t Port, ColorMode_t Mode, DataLogger* Logger=NULL);
  virtual
  ~Color ();
};

class ReflectedSensor : private Color
{
public:
  ReflectedSensor(Port_t Port, DataLogger* Logger=NULL);
  int GetReflected();
  virtual
  ~ReflectedSensor();
};

#endif /* COLOR_H_ */
