/*
 * IODevice.h
 *
 *  Created on: Nov 19, 2014
 *      Author: jordi
 */

#ifndef IODEVICE_H_
#define IODEVICE_H_

#include <string>
#include "FileIOChannel.h"

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


class IODevice
{
public:
  IODevice (Port_t Port);
  virtual
  ~IODevice ();
  virtual bool Connect(Port_t Port, const string Types[], const int NumTypes) = 0;
  void WritePropertyFile(string Attribute, string Value);
  bool m_Connected;
  int  m_DeviceIndex;
protected:
  string ReadPropertyFile(string File);
};

/*
 * Abstract class to manage any sensor
 */
class Sensor : public IODevice
{
public:
  Sensor(Port_t Port=INPUT_AUTO, const string Types[]=sEv3Sensor, int const NumTypes=NUM_OF_SUPPORTED_SENSORS);
  virtual
  ~Sensor();
  bool Connect(Port_t Port=INPUT_AUTO, const string Types[]=sEv3Sensor, const int NumTypes=NUM_OF_SUPPORTED_SENSORS);
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
  string m_DevicePath;
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



#endif /* IODEVICE_H_ */
