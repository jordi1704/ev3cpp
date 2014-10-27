/*
 * Motor.h
 *
 *  Created on: Oct 4, 2014
 *      Author: jordi
 */

#ifndef MOTOR_H_
#define MOTOR_H_


#include "Ev3Device.h"

using namespace std;

typedef int Speed_t;
typedef int Position_t;
typedef unsigned int Time_t;
typedef signed char Power_t;

#define MAX_SPEED_BIG_MOTOR     900
#define MAX_SPEED_SMALL_MOTOR  1200

enum stop_mode_t {COAST, BRAKE, HOLD, _STOP_MODES_};
const string sStopMode[_STOP_MODES_+1]={"coast","brake","hold" ,"stop_mode"};

enum run_mode_t  {RUN_FOREVER, RUN_FOR_TIME, RUN_TO_POSITION, _RUN_MODES_};
const string sRunMode[_RUN_MODES_+1]={"forever","time","position","run_mode"};

enum reg_mode_t {REG_ON, REG_OFF, _REG_MODES_};
// TODO eliminate underscores
const string sRegMode[_REG_MODES_+1]={"on","off","regulation_mode"};

const string sDutyCycle("duty_cycle_sp");
const string sPulsesPerSec("pulses_per_second_sp");
const string TIME_SP("time_sp");
const string POSITION("position");
const string POSITION_SP("position_sp");
// TODO capitalize string names

enum state_t {RUN, STOP, _STATE_MODES_};
const string sState[_STATE_MODES_+1]={"1","0","run"};


class Motor : public Ev3Device
{
public:
  Motor(Port_t Port, DataLogger* Logger=NULL);
  virtual ~Motor ();
  virtual void SetSpeed(Power_t Power);
  void RunForever(Power_t Power);
  void RunForTime(Power_t Power, Time_t Duration);
  void RunToPosition(Power_t Power, Position_t Position);
  Position_t GetPosition();
  void ResetPosition();
  void Stop();
protected:
  void SetRegulationMode(reg_mode_t RegMode);
private:
  virtual int CalculateSpeed(Power_t Power);
  reg_mode_t GetRegulationMode();
  reg_mode_t m_RegMode;
};

#endif /* MOTOR_H_ */
