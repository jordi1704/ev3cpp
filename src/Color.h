/*
 * Color.h
 *
 *  Created on: Oct 23, 2014
 *      Author: jordi
 */

#ifndef COLOR_H_
#define COLOR_H_

#include "Sensor.h"

enum ColorMode_t {REFLECTED, AMBIENT, COLOR, _COLOR_MODES_};
const string sColorMode[_COLOR_MODES_+1]={"COL-REFLECT","COL-AMBIENT",
                                          "COL-COLOR","mode"};

enum Color_t {NONE, BLACK, BLUE, GREEN, YELLOW, RED, WHITE, BROWN, COLORS};
const string sColor[COLORS]={"none", "black", "blue", "green",
			     "yellow", "red", "white","brown"};

const string sColorValue[_COLOR_MODES_]={"value0","value0","value0"};

class Color : public Sensor
{
public:
  Color (Port_t Port, ColorMode_t Mode, DataLogger* Logger=NULL);
  virtual
  ~Color ();
};

class LightSensor : private Color
{
public:
  LightSensor(Port_t Port, DataLogger* Logger=NULL);
  int GetReflected();
  virtual
  ~LightSensor();
};



#endif /* COLOR_H_ */
