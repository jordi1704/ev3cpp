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
  // TODO Auto-generated destructor stub
}

string IODevice::ReadPropertyFileStr(string Attribute)
{
  ifstream* ibuf=new ifstream();
  string sAttributeValue;
  ibuf->open(Attribute.c_str(),ios::in);
  *ibuf >> sAttributeValue;
  ibuf->close();
  delete ibuf;
  return sAttributeValue;
}

int IODevice::ReadPropertyFileInt(string Attribute)
{
  ifstream* ibuf=new ifstream();
  string sAttributeValue;
  ibuf->open(Attribute.c_str(),ios::in);
  *ibuf >> sAttributeValue;
  ibuf->close();
  delete ibuf;
  return atoi(sAttributeValue.c_str());
}

//TODO check if not possible to open file streams
void IODevice::WritePropertyFile(string Attribute, string Value)
{
  ofstream* obuf=new ofstream();
  obuf->open(Attribute.c_str(),ios::out);
  *obuf << Value;
  obuf->close();
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
      m_SensorValues=new InputStreams(m_NumValues,m_DevicePath);
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

//TODO carregar-se NumTypes
bool Sensor::Connect(Port_t Port, const string Types[], const int NumTypes)
{
  DIR *Directory;
  struct dirent* DirectoryEntry;
  string sDeviceType="sensor";
  string sDevicePath=SENSOR_PATH;
  string sInputPort;
  string sSensorType;

  Directory=opendir(sDevicePath.c_str());
  cout << "Open" <<endl;
  // Enumerate devices
  while((DirectoryEntry=readdir(Directory))!=NULL){

      if(strstr(DirectoryEntry->d_name,sDeviceType.c_str())){

	  // Store file path
	  m_DevicePath=sDevicePath+string(DirectoryEntry->d_name);
	  cout << m_DevicePath << endl;

	  //Determine port
	  m_PortName=ReadPropertyFileStr(m_DevicePath+"/port_name");

	  // Determine sensor type
	  m_TypeName=ReadPropertyFileStr(m_DevicePath+"/name");

	  // Determine Mode
	  m_Mode=ReadPropertyFileStr(m_DevicePath+"/mode");

	  // Determine num of values
	  m_NumValues=ReadPropertyFileInt(m_DevicePath+"/num_values");

	  // Determine sensor modes
	  m_Modes=ReadPropertyFileStr(m_DevicePath+"/modes");

	  cout << sInputPort << endl;
	  cout << sSensorType << endl;

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
  //TODO modify InputStreams to provide raw data and avoid string conversions
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


