/*
 * Color.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: jordi
 */

#include "Color.h"
#include "cutils.h"
#include <iostream>

Color::Color (Port_t Port, ColorMode_t Mode, DataLogger* Logger) :
							Sensor(Port,Logger)
{
  m_DeviceID=" COLOR:"+sPortName[Port];
  m_ColorMode=Mode;
  SetColorMode(Mode);
  Trace(m_Logger,COLOR_DBG_LVL,m_DeviceID+"-> Color sensor constructed");
}

Color::~Color ()
{
}

void Color::SetColorMode(ColorMode_t Mode)
{
  Sensor::SetSensorMode(sColorMode[Mode]);
  m_ColorMode=Mode;
  Trace(m_Logger,COLOR_DBG_LVL,m_DeviceID+"-> SetColorMode:"+sColorMode[Mode]);
}

LightSensor::LightSensor (Port_t Port, DataLogger* Logger) :
    Color(Port,REFLECTED,Logger)
{
  m_DeviceID=" LIGHT_SENSOR:"+sPortName[Port];
  Trace(m_Logger,LIGHTSENSOR_DBG_LVL,m_DeviceID+
        "-> LightSensor constructed");
}

LightSensor::~LightSensor()
{
}

int LightSensor::GetReflected()
{
  int ReflectedValue;
  if(m_ColorMode!=REFLECTED) SetColorMode(REFLECTED);
  ReflectedValue=atoi(GetSensorValue(sColorValue[REFLECTED]).c_str());
  Trace(m_Logger,LIGHTSENSOR_DBG_LVL,m_DeviceID+"-> GetReflected:"+
        ToString(ReflectedValue));
  return ReflectedValue;
}

int LightSensor::GetAmbient()
{
  int AmbientValue;
  if(m_ColorMode!=AMBIENT) SetColorMode(AMBIENT);
  AmbientValue=atoi(GetSensorValue(sColorValue[REFLECTED]).c_str());
  Trace(m_Logger,LIGHTSENSOR_DBG_LVL,m_DeviceID+"-> GetAmbient:"+
        ToString(AmbientValue));
  return AmbientValue;
}

Colorimeter::Colorimeter(Port_t Port, DataLogger* Logger) :
    Color(Port,COLOR,Logger)
{
  m_DeviceID=" COLORIMETER:"+sPortName[Port];
  Trace(m_Logger,COLORIMETER_DBG_LVL,m_DeviceID+"-> Colorimeter constructed");
}

Colorimeter::~Colorimeter()
{
}

Color_t Colorimeter::GetColor()
{
  unsigned char colorNumber;
  Color_t ColorDetected;
  if(m_ColorMode!=COLOR) SetColorMode(COLOR);
  colorNumber=atoi(Sensor::GetSensorValue(sColorValue[COLOR]).c_str());
  Trace(m_Logger,COLORIMETER_DBG_LVL,m_DeviceID+"-> GetColor:"+
  	sColor[colorNumber]);
  ColorDetected  = (colorNumber==NONE) ? NONE :
		    (colorNumber==BLACK) ? BLACK :
		     (colorNumber==BLUE) ? BLUE :
		      (colorNumber==GREEN) ? GREEN :
		       (colorNumber==YELLOW) ? YELLOW :
			(colorNumber==RED) ? RED :
			 (colorNumber==WHITE) ? WHITE :
			  (colorNumber==BROWN) ? BROWN : NONE;
  return ColorDetected;
}

