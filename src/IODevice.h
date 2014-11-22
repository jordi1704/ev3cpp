/*
 * IODevice.h
 *
 *  Created on: Nov 19, 2014
 *      Author: jordi
 */

#ifndef IODEVICE_H_
#define IODEVICE_H_

#include <string>

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

class IODevice
{
public:
  IODevice (Port_t Port);
  virtual
  ~IODevice ();
  bool m_Connected;
  int m_DeviceIndex;
  virtual bool Connect(Port_t Port) = 0;
//  virtual void SetProperty(string Property, string Value)=0;
//  virtual void SetProperty(string Property, int Value)=0;
//  virtual bool IsConnected()=0;
//  virtual int  GetDeviceIndex()=0;
};

class Sensor : public IODevice
{
public:
  Sensor(Port_t Port=INPUT_AUTO, string Types[]=NULL, int NumTypes=0);
  virtual
  ~Sensor();
  bool Connect(Port_t Port=INPUT_AUTO);
private:
  string m_DevicePath;
};



#endif /* IODEVICE_H_ */
