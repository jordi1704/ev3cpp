/*
 * IODevice.cpp
 *
 *  Created on: Nov 19, 2014
 *      Author: jordi
 */

#include "IODevice.h"
#include "globalDefs.h"
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <string.h>
#include <sstream>



IODevice::IODevice (Port_t Port)
{
  m_Connected=false;
  m_DeviceIndex=0;
}

IODevice::~IODevice ()
{
}

string IODevice::ReadPropertyFile(string Attribute)
{
  // Allow reading properties only for non-enumerated or connected devices
  if(!m_DeviceIndex || m_Connected){
    string Data;
    FileIOChannel PropFile(Attribute);
    PropFile.GetData(Data);
    return Data;
  } else {
      cout << "***ERROR*** Trying to read from an unconnected device" << endl;
      exit(-1);
  }
}

void IODevice::WritePropertyFile(string Attribute, string Value)
{
  // Allow writing properties only for connected devices
  if(m_Connected){
    FileIOChannel PropFile(Attribute);
    PropFile.SendData(Value);
  } else {
    cout << "***ERROR*** Trying to write to an unconnected device" << endl;
    exit(-1);
  }
}

Sensor::Sensor(Port_t Port, const string Types[], const int NumTypes)
  : IODevice(Port)
{
  m_SensorValues=NULL;
  m_NumValues=0;
  m_PortName="";
  m_TypeName="";
  m_Mode="";
  m_Connected=this->Connect(Port, Types, NumTypes);
  if(m_Connected){
      m_SensorValues=new InputChannels(m_NumValues,m_DevicePath);
  }
}

Sensor::~Sensor(){
  if(!m_SensorValues) delete m_SensorValues;
};

void Sensor::SetMode(string Mode)
{
  stringstream ssAllowedModes(m_Modes);
  string sAllowedMode;
  while(ssAllowedModes >> sAllowedMode){
      if(Mode==sAllowedMode) IODevice::WritePropertyFile(m_DevicePath+"/mode",
                                                         Mode);
      return;
  }
  // If wrong mode set, disconnect sensor
  cout << "Error seting mode " << Mode << endl;
  m_Connected=false;
}

bool Sensor::Connect(Port_t Port, const string Types[], const int NumTypes)
{
  DIR *Directory;
  struct dirent* DirectoryEntry;
  string sDeviceType="sensor";
  string sDevicePath=SENSOR_PATH;
  string sInputPort;
  string sSensorType;

  Directory=opendir(sDevicePath.c_str());

  // Enumerate devices
  while((DirectoryEntry=readdir(Directory))!=NULL){

      if(strstr(DirectoryEntry->d_name,sDeviceType.c_str())){

	  // Store file path
	  m_DevicePath=sDevicePath+string(DirectoryEntry->d_name);

	  //Determine port
	  m_PortName=ReadPropertyFile(m_DevicePath+"/port_name");

	  // Determine sensor type
	  m_TypeName=ReadPropertyFile(m_DevicePath+"/name");

	  // Determine Mode
	  m_Mode=ReadPropertyFile(m_DevicePath+"/mode");

	  // Determine num of values
	  m_NumValues=atoi(ReadPropertyFile(m_DevicePath+"/num_values").c_str());

	  // Determine sensor modes
	  m_Modes=ReadPropertyFile(m_DevicePath+"/modes");

	  // Match sensor port and type
	  for (int i = 0; i < NumTypes; ++i) {
	    cout << "Comparing " << m_TypeName << " with "<< Types[i] << endl;
	    if (m_TypeName.find(Types[i])!=m_TypeName.npos) {
		switch (Port) {
		  case INPUT_AUTO:
		    for (int port = INPUT_1; port <= INPUT_4; ++port) {
			if(m_PortName==sPort[port]){
			    m_DeviceIndex=port;
			}
		    }
		    cout << "Connected type " << m_TypeName << " on " << m_PortName<< endl;
		    return true;
		    break;
		  case INPUT_1:
		  case INPUT_2:
		  case INPUT_3:
		  case INPUT_4:
		    if(m_PortName==sPort[Port]){
			m_DeviceIndex=Port;
			cout << "Connected type " << m_TypeName << " on " << m_PortName<< endl;
			return true;
		    } else {
			cout << "Sensor is available but not connected to " << sPort[Port] << endl;
			return false;
		    }
		  default:
		    cout << "Sensor can only be connected to input port" << endl;
		    return false;
		    break;
		}
	    }
	  }
      } // end find sensor
  } // end while
  cout << "unable to find any sensor of allowed types" << endl;
  return false;
};



int Sensor::GetValue(int ValueIndex)
{
  string sResult;
  m_SensorValues->GetData(ValueIndex,sResult);
  return atoi(sResult.c_str());
}

float Sensor::GetFloatValue(int ValueIndex)
{
  string sResult;
  m_SensorValues->GetData(ValueIndex,sResult);
  return atof(sResult.c_str());
}



Touch::Touch(Port_t Port) : Sensor(Port,&sEv3Sensor[EV3_TOUCH_SENSOR],1)
{
  this->InitSensor();
};

Touch::~Touch (){};

void Touch::InitSensor()
{
  Sensor::SetMode("TOUCH");
}

bool Touch::IsPressed()
{
  return (Sensor::GetValue(0)==1);
}


