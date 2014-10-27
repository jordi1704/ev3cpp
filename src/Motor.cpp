/*
 * Motor.cpp
 *
 *  Created on: Oct 4, 2014
 *      Author: jordi
 */

#include "Motor.h"
#include "Ev3Device.h"
#include "cutils.h"


using namespace std;

/*
 * Motor constructor
 *
 * It constructs a regulated motor, since this modes is available for
 * tacho and mini-tacho motors
 *
 */
Motor::Motor(Port_t Port, DataLogger* Logger) : Ev3Device(Port,Logger)
{
  this->SetRegulationMode(REG_ON);
  m_RegMode=REG_ON;
  m_DeviceID=" MOTOR:"+sPortName[Port];
  Trace(m_Logger,MOTOR_DBG_LVL,m_DeviceID+"-> Constructed regulated motor");
}

/*
 * Motor destructor
 *
 * Before destructing the motor, it stops it to avoid leaving it running
 * under no control
 *
 */
Motor::~Motor ()
{
  this->Stop();
  Trace(m_Logger,MOTOR_DBG_LVL,m_DeviceID+"-> Motor stopped and destroyed");
}

Position_t Motor::GetPosition()
{
  Position_t Position=atoi(GetDeviceParameter(POSITION).c_str());
  Trace(m_Logger,MOTOR_DBG_LVL,m_DeviceID+"-> GetPosition: "+
        ToString(Position));
  return Position;
}

void Motor::ResetPosition()
{
  this->SetDeviceParameter(POSITION,"0");
  Trace(m_Logger,MOTOR_DBG_LVL,m_DeviceID+"-> ResetPosition");
}

int Motor::CalculateSpeed(Power_t Power)
{
  // Determine pulses per second taking Power as a percentage.
  // Assume a big motor is being driven (MAX_SPEED_BIG_MOTOR) in order
  // not to exceed speed
  return (Power*MAX_SPEED_BIG_MOTOR)/100;
}

void Motor::SetSpeed(Power_t Power)
{
  string Speed,Parameter;
  switch (m_RegMode) {
    case REG_ON:
      Speed=ToString(CalculateSpeed(Power));
      Parameter=sPulsesPerSec;
      break;
    case REG_OFF:
      Speed=ToString(Power);
      Parameter=sDutyCycle;
      break;
    default:
      break;
  }
  this->SetDeviceParameter(Parameter,Speed);
  Trace(m_Logger,MOTOR_DBG_LVL,m_DeviceID+"-> SetSpeed: "+string(Speed));
}

void Motor::SetRegulationMode(reg_mode_t RegMode)
{
  this->SetDeviceParameter(sRegMode[_REG_MODES_],sRegMode[RegMode]);
  m_RegMode=this->GetRegulationMode();
  Trace(m_Logger,MOTOR_DBG_LVL,m_DeviceID+"-> SetRegulationMode: "+
        sRegMode[RegMode]);
}

reg_mode_t Motor::GetRegulationMode()
{
  string sRegulationMode=GetDeviceParameter(sRegMode[_REG_MODES_]);
  Trace(m_Logger,MOTOR_DBG_LVL,m_DeviceID+"-> GetRegulationMode: "+
        sRegulationMode);
  if (sRegulationMode==sRegMode[REG_ON])
    return REG_ON;
  else
    return REG_OFF;
}

void Motor::RunForever(Power_t Power)
{
  this->SetDeviceParameter(sRunMode[_RUN_MODES_],sRunMode[RUN_FOREVER]);
  this->SetSpeed(Power);
  this->SetDeviceParameter(sState[_STATE_MODES_],sState[RUN]);
  Trace(m_Logger,MOTOR_DBG_LVL,m_DeviceID+"-> RunForever: "+ToString(Power));
}

void Motor::RunForTime(Power_t Power, Time_t Duration)
{
  this->SetDeviceParameter(sRunMode[_RUN_MODES_],sRunMode[RUN_FOR_TIME]);
  this->SetDeviceParameter(TIME_SP,ToString(Duration));
  this->SetSpeed(Power);
  this->SetDeviceParameter(sState[_STATE_MODES_],sState[RUN]);
  Trace(m_Logger,MOTOR_DBG_LVL,m_DeviceID+"-> RunForTime: "+
        ToString(Power)+"  Duration: "+ToString(Duration));
}

void Motor::RunToPosition(Power_t Power, Position_t Position)
{
  this->SetDeviceParameter(sRunMode[_RUN_MODES_],sRunMode[RUN_TO_POSITION]);
  this->SetDeviceParameter(POSITION_SP,ToString(Position));
  this->SetSpeed(Power);
  this->SetDeviceParameter(sState[_STATE_MODES_],sState[RUN]);
  Trace(m_Logger,MOTOR_DBG_LVL,m_DeviceID+"-> RunToPosition: "+
          ToString(Power)+"  Position: "+ToString(Position));
}

void Motor::Stop()
{
  this->SetDeviceParameter(sState[_STATE_MODES_],sState[STOP]);
  Trace(m_Logger,MOTOR_DBG_LVL,m_DeviceID+"-> Stop");
}



