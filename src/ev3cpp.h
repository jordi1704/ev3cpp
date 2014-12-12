/*
 * IODevice.h
 *
 *  Created on: Nov 19, 2014
 *      Author: jordi
 */

#ifndef IODEVICE_H_
#define IODEVICE_H_

#include "FileIOChannel.h"

#define SENSOR_PATH   		"/sys/class/msensor/"
#define MOTOR_PATH 		"/sys/class/tacho-motor/"

using namespace std;


enum Port_t { INPUT_AUTO,
	      INPUT_1, INPUT_2, INPUT_3, INPUT_4,
	      OUTPUT_AUTO,
	      OUTPUT_A, OUTPUT_B, OUTPUT_C, OUTPUT_D
              };

const string sPort[10]={  "input_auto",
			  "in1", "in2", "in3", "in4",
			  "output_auto",
			  "outA","outB","outC","outD"
			};

// Only EV3 sensors are supported
enum Ev3Sensor_t {EV3_TOUCH_SENSOR,
                  EV3_IR_SENSOR,
                  EV3_GYRO_SENSOR,
                  NUM_OF_SUPPORTED_SENSORS
		 };

const string sEv3Sensor[]={"lego-ev3-touch",
			   "ev3-uart-33"   ,
			   "ev3-uart-32"
			  };

enum Ev3Motor_t {
		 EV3_TACHO_MOTOR,
		 EV3_MINITACHO_MOTOR,
		 NUM_OF_SUPPORTED_MOTORS
		};

const string sEv3Motor[]={"tacho","minitacho"};

class IODevice
{
public:
  IODevice (Port_t Port);
  virtual
  ~IODevice ();
  virtual bool Connect(Port_t Port, const string Types[],
                       const int NumTypes) = 0;
  void WritePropertyFile(string Attribute, string Value);
  bool m_Connected;
  int  m_DeviceIndex;
protected:
  string m_DevicePath;
  string ReadPropertyFile(string File);
};

/*
 * Abstract class to manage any sensor
 */
class Sensor : public IODevice
{
public:
  Sensor(Port_t Port=INPUT_AUTO, const string Types[]=sEv3Sensor,
         const int NumTypes=NUM_OF_SUPPORTED_SENSORS);
  virtual
  ~Sensor();
  bool Connect(Port_t Port=INPUT_AUTO, const string Types[]=sEv3Sensor,
               const int NumTypes=NUM_OF_SUPPORTED_SENSORS);
  int GetValue(int ValueIndex);
  float GetFloatValue(int ValueIndex);
  void SetMode(string Mode);
  virtual void InitSensor()=0;
  string m_PortName;
  string m_TypeName;
  string m_Mode;
  string m_Modes;
  int m_NumValues;
private:
  InputChannels* m_SensorValues;
};

class Touch : private Sensor
{
public:
  Touch (Port_t Port=INPUT_AUTO);
  virtual
  ~Touch ();
  bool IsPressed();
private:
  void InitSensor();
};

class Gyro : private Sensor
{
public:
  Gyro (Port_t Port=INPUT_AUTO);
  virtual
  ~Gyro ();
  short int GetRotationalSpeed();
private:
  void InitSensor();
};

/*
 * Abstract class to manage any motor
 */
class Motor : public IODevice
{
public:
  Motor (Port_t Port=OUTPUT_AUTO, const string Type="");
  virtual
  ~Motor();
  void Reset();
  bool Connect(Port_t Port=OUTPUT_AUTO, const string Types[]=sEv3Motor,
                 const int NumTypes=NUM_OF_SUPPORTED_MOTORS);
  virtual void InitMotor()=0;
  int m_DutyCycle;
  int m_DutyCycleSP;
  string m_PortName;
  int m_Position;
  string m_PositionMode;
  int m_PositionSP;
  int m_PulsesPerSecond;
  int m_PulsesPerSecondSP;
  int m_RampUpSP;
  int m_RampDownSP;
  string m_RegulationMode;
  int m_Run;
  string m_RunMode;
  int m_SpeedRegulationP;
  int m_SpeedRegulationI;
  int m_SpeedRegulationD;
  int m_SpeedRegulationK;
  string m_State;
  string m_StopMode;
  string* m_StopModes;
  int m_TimeSP;
  string m_Type;
};

class ServoMotor : private Motor
{
public:
  ServoMotor(Port_t Port=OUTPUT_AUTO);
  virtual
  ~ServoMotor();
  void SetPower(int Power);
  int GetPosition();
private:
  void InitMotor();
  FileIOChannel* SpeedFastUpdateChannel;
};


#endif /* IODEVICE_H_ */
