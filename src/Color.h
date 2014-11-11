/*
 * Color.h
 *
 *  Created on: Oct 23, 2014
 *      Author: jordi
 */

#ifndef COLOR_H_
#define COLOR_H_

#include "Sensor.h"

enum ColorMode_t {REFLECTED, AMBIENT, COLOR, COLOR_MODES};
const string sColorMode[COLOR_MODES+1]={"COL-REFLECT","COL-AMBIENT",
                                          "COL-COLOR","mode"};

enum Color_t {NONE, BLACK, BLUE, GREEN, YELLOW, RED, WHITE, BROWN, COLORS};
const string sColor[COLORS]={"none", "black", "blue", "green",
			     "yellow", "red", "white","brown"};

const string sColorValue[COLOR_MODES]={"value0","value0","value0"};

class Color : public Sensor
{
public:
  Color (Port_t Port, ColorMode_t Mode, DataLogger* Logger=NULL);
  virtual
  ~Color ();
  void SetColorMode(ColorMode_t Mode);
};

class LightSensor : private Color
{
public:
  LightSensor(Port_t Port, DataLogger* Logger=NULL);
  virtual
    ~LightSensor();
  int GetReflected();
  int GetAmbient();
};

class Colorimeter : private Color
{
public:
  Colorimeter(Port_t Port, DataLogger* Logger=NULL);
  virtual
  ~Colorimeter();
  Color_t GetColor();
};



#endif /* COLOR_H_ */
