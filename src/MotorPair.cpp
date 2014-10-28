/*
 * Tank.cpp
 *
 *  Created on: Oct 15, 2014
 *      Author: jordi
 */

#include "MotorPair.h"
#include <iostream>
#include "cutils.h"

void MotorPair::Pivot(Power_t Power)
{
  MotorL->RunForever(Power);
  MotorR->RunForever(-Power);
}

void MotorPair::Turn(float Angle, Power_t Power)
{
  Power_t PowerL, PowerR;
  PowerL=Power;
  PowerR=static_cast<Power_t>(float(Power*(1.0-Angle/90.0)));
  //If turning left, swap power values between left & right motors
  if (Angle<0.0) swap(PowerL,PowerR);
  MotorL->RunForever(PowerL);
  MotorR->RunForever(PowerR);
}

MotorPair::MotorPair (Port_t LeftPort, Port_t RightPort,DataLogger* Logger)
{
  MotorL=new Tacho(LeftPort,Logger);
  MotorR=new Tacho(RightPort,Logger);
  MotorL->SetRegulationMode(REG_ON);
  MotorR->SetRegulationMode(REG_ON);
}

MotorPair::~MotorPair ()
{
  MotorL->~Tacho();
  MotorR->~Tacho();
}

