/*
 * Motor.h
 *
 *  Created on: Oct 4, 2014
 *      Author: jordi
 */

#ifndef MOTOR_H_
#define MOTOR_H_


#include "Ev3Device.h"
#include "DirectIO.h"

using namespace std;

typedef int Speed_t;
typedef int Position_t;
typedef unsigned int Time_t;
typedef signed char Power_t;

#define MAX_SPEED_BIG_MOTOR     900
#define MAX_SPEED_SMALL_MOTOR  1200

enum stop_mode_t {COAST, BRAKE, HOLD, STOP_MODES};
const string sStopMode[STOP_MODES+1]={"coast","brake","hold" ,"stop_mode"};

enum run_mode_t  {RUN_FOREVER, RUN_FOR_TIME, RUN_TO_POSITION, RUN_MODES};
const string sRunMode[RUN_MODES+1]={"forever","time","position","run_mode"};

enum reg_mode_t {REG_ON, REG_OFF, REG_MODES};
const string sRegMode[REG_MODES+1]={"on","off","regulation_mode"};

enum state_t {RUN, STOP, STATE_MODES};
const string sState[STATE_MODES+1]={"1","0","run"};


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
  virtual int CalculateSpeed(Power_t Power);
protected:
  // To allow only certain kind of motors to change regulation mode
  // For example, Tacho motors will be allowed, whereas MiniTacho won't
  void SetRegulationMode(reg_mode_t RegMode);
private:
  reg_mode_t GetRegulationMode();
  reg_mode_t m_RegMode;
};

class ServoMotor : public Motor
{
public:
  ServoMotor(Port_t Port, DataLogger* Logger=NULL);
  void SetSpeed(Power_t Power);
  virtual ~ServoMotor();
private:
  dirIO::DirectIO* m_OutStream;
};





#endif /* MOTOR_H_ */
