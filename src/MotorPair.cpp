/*
 * Tank.cpp
 *
 *  Created on: Oct 15, 2014
 *      Author: jordi
 */

#include "MotorPair.h"
#include <iostream>
#include "cutils.h"
#include <cmath>

MotorPair::MotorPair (Port_t LeftPort, Port_t RightPort, DataLogger* Logger)
{
  MotorL=new Tacho(LeftPort,Logger);
  MotorR=new Tacho(RightPort,Logger);
  MotorL->SetRegulationMode(REG_ON);
  MotorR->SetRegulationMode(REG_ON);
  m_DeviceID=" MOTORPAIR:"+sPortName[LeftPort]+":"+sPortName[RightPort];
  m_Logger=Logger;
  Trace(m_Logger, MOTORPAIR_DBG_LVL, m_DeviceID+FUNCT_STR);
}

MotorPair::~MotorPair ()
{
  MotorL->~Tacho();
  MotorR->~Tacho();
  Trace(m_Logger, MOTORPAIR_DBG_LVL, m_DeviceID+FUNCT_STR);
}

void MotorPair::Pivot(Power_t Power)
{
  MotorL->RunForever(Power);
  MotorR->RunForever(-Power);
  Trace(m_Logger, MOTORPAIR_DBG_LVL, m_DeviceID+FUNCT_STR+ToString(Power));
}

void MotorPair::Straight(Power_t Power)
{
  MotorL->RunForever(Power);
  MotorR->RunForever(Power);
  Trace(m_Logger, MOTORPAIR_DBG_LVL, m_DeviceID+FUNCT_STR+ToString(Power));
}

void MotorPair::Turn(float Angle, Power_t Power)
{
  Power_t PowerL, PowerR;
  PowerL=Power;
  PowerR=static_cast<Power_t>(Power*(1.0f-abs(Angle)/90.0f));

  //If turning left, swap power values between left & right motors
  if (Angle<0.0) swap(PowerL,PowerR);
  MotorL->RunForever(PowerL);
  MotorR->RunForever(PowerR);
  Trace(m_Logger, MOTORPAIR_DBG_LVL, m_DeviceID+FUNCT_STR+ToString(Power));
}


