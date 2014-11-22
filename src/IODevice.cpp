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



IODevice::IODevice (Port_t Port)
{
  // TODO Auto-generated constructor stub
  m_Connected=false;
  m_DeviceIndex=0;
}

IODevice::~IODevice ()
{
  // TODO Auto-generated destructor stub
}


Sensor::Sensor(Port_t Port, string Types[], int NumTypes)
  : IODevice(Port)
{
  m_Connected=this->Connect(Port);
}

bool Sensor::Connect(Port_t Port)
{
  DIR *Directory;
  struct dirent* DirectoryEntry;
  string sDeviceType="sensor";
  string sDevicePath=SENSOR_PATH;
  ifstream* m_ibuf;
  string sInputPort;

  Directory=opendir(sDevicePath.c_str());
  cout << "Open" <<endl;
  while((DirectoryEntry=readdir(Directory))!=NULL){
      if(strstr(DirectoryEntry->d_name,sDeviceType.c_str())){
	  // Store file path
	  m_DevicePath=sDevicePath+string(DirectoryEntry->d_name);
	  cout << m_DevicePath << endl;
	  // Get Port string
	  m_ibuf=new ifstream();
	  m_ibuf->open((m_DevicePath+"/port_name").c_str(),ios::in);
	  *m_ibuf >> sInputPort;
	  m_ibuf->close();
	  cout << sInputPort << endl;
	  switch (Port) {
	    case INPUT_AUTO:
	      for (int port = INPUT_1; port <= INPUT_4; ++port) {
		  if(sInputPort==sPort[port]){
		      m_DeviceIndex=port;
		      break;
		  }
	      }
	      return true;
	      break;
	    case INPUT_1:
	    case INPUT_2:
	    case INPUT_3:
	    case INPUT_4:
	      if(sInputPort==sPort[Port]){
		  m_DeviceIndex=Port;
		  return true;
	      } else {
		  cout << "Sensor is not connected to " << sPort[Port] << endl;
		  return false;
	      }
	    default:
	      cout << "Sensor cannot be connected to output port" << endl;
	      return false;
	      break;
	  }
      }
  }
  cout << "unable to find sensor" << endl;
  return false;
};

Sensor::~Sensor(){
};




