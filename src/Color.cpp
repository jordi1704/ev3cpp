/*
 * Color.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: jordi
 */

#include "Color.h"
#include <iostream>

Color::Color (Port_t Port, ColorMode_t Mode, DataLogger* Logger) :
							Sensor(Port,Logger)
{
  m_DeviceID=" COLOR:"+sPortName[Port];
  m_ColorMode=Mode;
  SetColorMode(Mode);
}

Color::~Color ()
{
}

void Color::SetColorMode(ColorMode_t Mode)
{
  Sensor::SetSensorMode(sColorMode[Mode]);
}

LightSensor::LightSensor (Port_t Port, DataLogger* Logger) :
    Color(Port,REFLECTED,Logger)
{
  m_DeviceID=" LIGHT_SENSOR:"+sPortName[Port];
}

LightSensor::~LightSensor()
{
}

int LightSensor::GetReflected()
{
  if(m_ColorMode!=REFLECTED) SetColorMode(REFLECTED);
  return atoi(GetSensorValue(sColorValue[REFLECTED]).c_str());
}

int LightSensor::GetAmbient()
{
  if(m_ColorMode!=AMBIENT) SetColorMode(AMBIENT);
  return atoi(GetSensorValue(sColorValue[AMBIENT]).c_str());
}

ColorSensor::ColorSensor(Port_t Port, DataLogger* Logger) :
    Color(Port,COLOR,Logger)
{
  m_DeviceID=" COLOR_SENSOR:"+sPortName[Port];
}

ColorSensor::~ColorSensor()
{
}

Color_t ColorSensor::GetColor()
{
  string color;
  if(m_ColorMode!=COLOR) SetColorMode(COLOR);
  color=Sensor::GetSensorValue(sColorValue[COLOR]);
  return (color==sColor[NONE]) ? NONE :
	  (color==sColor[BLACK]) ? BLACK :
	   (color==sColor[BLUE]) ? BLUE :
	    (color==sColor[GREEN]) ? GREEN :
             (color==sColor[YELLOW]) ? YELLOW :
              (color==sColor[RED]) ? RED :
               (color==sColor[WHITE]) ? WHITE :
        	(color==sColor[BROWN]) ? BROWN : NONE;

}

