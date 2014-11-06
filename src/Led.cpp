/*
 * Led.cpp
 *
 *  Created on: Nov 4, 2014
 *      Author: jordi
 */

#include "Led.h"
#include "cutils.h"

LedMono::LedMono (Port_t Port, DataLogger* Logger) : Ev3Device(Port,Logger)
{
  m_DeviceID=" LED:"+sPortName[Port];
  Trace(m_Logger,LED_DBG_LVL,m_DeviceID+FUNCT_STR);
}

LedMono::~LedMono ()
{
  Trace(m_Logger,LED_DBG_LVL,m_DeviceID+FUNCT_STR);
}

Led::Led (LedPosition_t Position, DataLogger* Logger)
{
  switch (Position) {
    case LEFT:
      RedLed=new LedMono(LED_RED_LEFT, Logger);
      GreenLed=new LedMono(LED_GREEN_LEFT, Logger);
      m_DeviceID=" LEFT_LED:";
      break;
    case RIGHT:
      RedLed=new LedMono(LED_RED_RIGHT, Logger);
      GreenLed=new LedMono(LED_GREEN_RIGHT, Logger);
      m_DeviceID=" RIGHT_LED:";
      break;
    default:
      break;
  }
  m_Logger=Logger;
  Trace(Logger,LED_DBG_LVL,m_DeviceID+FUNCT_STR);
}

Led::~Led ()
{
  RedLed->~LedMono();
  GreenLed->~LedMono();
  Trace(m_Logger,LED_DBG_LVL,m_DeviceID+FUNCT_STR);
}

void Led::SetColor(LedColor_t Color)
{
  switch (Color) {
    case RED:
      RedLed->SetDeviceParameter("brightness","255");
      GreenLed->SetDeviceParameter("brightness","0");
      break;
    case GREEN:
      RedLed->SetDeviceParameter("brightness","0");
      GreenLed->SetDeviceParameter("brightness","255");
      break;
    case ORANGE:
      RedLed->SetDeviceParameter("brightness","127");
      GreenLed->SetDeviceParameter("brightness","127");
      break;
    default:
      RedLed->SetDeviceParameter("brightness","0");
      GreenLed->SetDeviceParameter("brightness","0");
      break;
  }
  Trace(m_Logger,LED_DBG_LVL,m_DeviceID+FUNCT_STR+sLedColor[Color]);
}

