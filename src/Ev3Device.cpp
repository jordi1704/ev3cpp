/*
 * Ev3Device.cpp
 *
 *  Created on: Oct 12, 2014
 *      Author: jordi
 */

#include "Ev3Device.h"
#include <string.h>
#include <iostream>
#include <dirent.h>

#define MOTOR_PATH    		"/sys/bus/legoev3/devices"
#define SENSOR_PATH   		"/sys/class/msensor"
#define PORT_NAME 		"/port_name";
#define MAX_FILENAME_LENGTH 	64

/*
 * Ev3Device constructor.
 *
 * It allows to create any EV3 component (motor or sensor) and get its
 * file path on ev3dev filesystem for further addressing
 *
 */
Ev3Device::Ev3Device (Port_t Port, DataLogger* Logger)
{
  m_DeviceID=" EV3DEVICE:"+sPortName[Port];
  m_DevicePath=GetDevicePath(Port);
  m_Logger=Logger;
  Trace(m_Logger,EV3DEVICE_DBG_LVL,m_DeviceID+"-> Constructed EV3 device");
}

/*
 * Ev3Device destructor
 */
Ev3Device::~Ev3Device ()
{
  Trace(m_Logger,EV3DEVICE_DBG_LVL,m_DeviceID+"-> EV3 device destroyed");
}

/*
 * Obtain the full ev3dev path for any Ev3Device connected on a particular
 * port.
 *
 */
string Ev3Device::GetDevicePath(Port_t Port)
{
  char PortPath[MAX_FILENAME_LENGTH];
  const char SensorParameter[]=PORT_NAME;

  string sResponse;
  string sOutPort;

  DIR *Directory;
  struct dirent* DirectoryEntry;

  switch (Port) {
    // Find sensor path name
    case IN_1:
    case IN_2:
    case IN_3:
    case IN_4:
      Directory=opendir(SENSOR_PATH);
      // Poll the "port_name" property of every sensor under /sys/class/msensor
      // until the specified input port is found
      while((DirectoryEntry=readdir(Directory))!=NULL){
	strcpy(PortPath,DirectoryEntry->d_name);
	strcat(PortPath,SensorParameter);
	ifstream inf(PortPath);
	getline(inf,sResponse);
	if(sResponse==sPortName[Port]){
	  Trace(m_Logger,EV3DEVICE_DBG_LVL,m_DeviceID+"-> Got file path:"
			+DirectoryEntry->d_name);
	  return DirectoryEntry->d_name;
	}
      }
      break;
    // Find motor path name
    case OUT_A:
    case OUT_B:
    case OUT_C:
    case OUT_D:
      sOutPort=MOTOR_PATH+string("/")+sPortName[Port]+string("/")+
               sPortName[Port]+string(":ev3-tacho-motor/tacho-motor");
      Directory=opendir(sOutPort.c_str());
      DirectoryEntry=readdir(Directory);
      Trace(m_Logger,EV3DEVICE_DBG_LVL,m_DeviceID+"-> Got file path:"
            	            +DirectoryEntry->d_name);
      return DirectoryEntry->d_name;
    default:
      break;
  }
  // Log error condition, terminate logger and exit program
  Trace(m_Logger,EV3DEVICE_DBG_LVL,m_DeviceID+
	" ***ERROR*** Attempting to attach device to port: "+sPortName[Port]);
  m_Logger->~DataLogger();
  exit(-1);
}

/*
 * Set any particular Ev3Device parameter to any Value via output file stream
 */
void Ev3Device::SetDeviceParameter(string Parameter, string Value)
{
  ofstream outf((m_DevicePath + "/" + Parameter).c_str(),ios::out);
  if (!outf) {
    // Log error condition, terminate logger and exit program
    Trace(m_Logger,EV3DEVICE_DBG_LVL,m_DeviceID+
	  " ***ERROR*** opening write stream for device ");
    m_Logger->~DataLogger();
    exit(-1);
  }
  outf << Value;
  Trace(m_Logger,EV3DEVICE_DBG_LVL,m_DeviceID+"-> SetDeviceParameter:"+
	Parameter+" to value:"+Value);
  outf.close();
}

/*
 * Get any particular Ev3Device parameter via input file stream
 */
string Ev3Device::GetDeviceParameter (string Parameter)
{
  ifstream inf((m_DevicePath + "/" + Parameter).c_str());
  if (!inf) {
    // Log error condition, terminate logger and exit program
    Trace(m_Logger,EV3DEVICE_DBG_LVL,m_DeviceID+
    " ***ERROR*** opening read stream for device ");
    m_Logger->~DataLogger();
    exit(-1);
  }
  string sResponse;
  getline(inf,sResponse);
  inf.close();
  Trace(m_Logger,EV3DEVICE_DBG_LVL,m_DeviceID+"-> GetDeviceParameter:"+
            Parameter+" got value:"+sResponse);
  return sResponse;
}





