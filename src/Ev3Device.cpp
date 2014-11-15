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

#define MOTOR_PATH    		"/sys/class/tacho-motor/"
#define SENSOR_PATH   		"/sys/class/msensor/"
#define LED_PATH                "/sys/class/leds/"
#define MAX_FILENAME_LENGTH 	256

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
  m_Logger=Logger;
  this->SetDevicePath(Port);
  Trace(m_Logger,EV3DEVICE_DBG_LVL,m_DeviceID+FUNCT_STR);
}

/*
 * Ev3Device destructor
 */
Ev3Device::~Ev3Device ()
{
  Trace(m_Logger,EV3DEVICE_DBG_LVL,m_DeviceID+FUNCT_STR);
}

/*
 * Obtain the full ev3dev path for any Ev3Device connected on a particular
 * port.
 *
 */
void Ev3Device::SetDevicePath(Port_t Port)
{
  char PortPath[MAX_FILENAME_LENGTH];
  char PortName[MAX_FILENAME_LENGTH];
  string sResponse;
  DIR *Directory;
  struct dirent* DirectoryEntry;
  string deviceType;
  string deviceTypePath;

  // Determine sensor, motor or led path. Everything connected to an IN port is
  // assumed to be a sensor. Conversely, OUT connected devices are assumed
  // to be motors.
  switch (Port) {
    case IN_1:case IN_2:case IN_3:case IN_4:
      deviceType="sensor";
      deviceTypePath=SENSOR_PATH;
      break;
    case OUT_A:case OUT_B:case OUT_C:case OUT_D:
      deviceType="tacho-motor";
      deviceTypePath=MOTOR_PATH;
      break;
    case LED_GREEN_LEFT:case LED_GREEN_RIGHT:
    case LED_RED_LEFT:case LED_RED_RIGHT:
      deviceType=sPortName[Port];
      deviceTypePath=LED_PATH;
      strcpy(PortPath,(deviceTypePath+deviceType).c_str());
      m_DevicePath=PortPath;
      return;
      break;
    default:
      break;
  }
  // Poll the "port_name" property of every device until it matches the
  // requested Port connection
  Directory=opendir(deviceTypePath.c_str());
  if(!Directory){
      Trace(m_Logger,EV3DEVICE_DBG_LVL,m_DeviceID+ERROR_STR+deviceTypePath);
        m_Logger->~DataLogger();
        exit(-1);
  }
  while((DirectoryEntry=readdir(Directory))!=NULL){
    if(strstr(DirectoryEntry->d_name,deviceType.c_str())){
      strcpy(PortPath,deviceTypePath.c_str());
      strcat(PortPath,DirectoryEntry->d_name);
      strcpy(PortName,PortPath);
      strcat(PortName,"/port_name");
      ifstream inf(PortName);
      getline(inf,sResponse);
      if(sResponse==sPortName[Port]){
	Trace(m_Logger,EV3DEVICE_DBG_LVL,m_DeviceID+FUNCT_STR+PortPath);
	m_DevicePath=PortPath;
	return;
      }
    }
  }
  // If there is not match, log error condition, terminate logger
  // and exit program
  Trace(m_Logger,EV3DEVICE_DBG_LVL,m_DeviceID+ERROR_STR+sPortName[Port]);
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
    Trace(m_Logger,EV3DEVICE_DBG_LVL,m_DeviceID+ERROR_STR);
    m_Logger->~DataLogger();
    exit(-1);
  }
  outf << Value;
  Trace(m_Logger,EV3DEVICE_DBG_LVL,m_DeviceID+FUNCT_STR+Parameter+","+Value);
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
    Trace(m_Logger,EV3DEVICE_DBG_LVL,m_DeviceID+ERROR_STR);
    m_Logger->~DataLogger();
    exit(-1);
  }
  string sResponse;
  getline(inf,sResponse);
  inf.close();
  Trace(m_Logger,EV3DEVICE_DBG_LVL,m_DeviceID+FUNCT_STR+Parameter+","
        +sResponse);
  return sResponse;
}

string Ev3Device::GetDevicePath()
{
  return m_DevicePath;
}





