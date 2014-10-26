/*
 * Ev3Device.cpp
 *
 *  Created on: Oct 12, 2014
 *      Author: jordi
 */

#include "Ev3Device.h"
#include <string.h>
#include <iostream>

#define MOTOR_PATH    		"/sys/bus/legoev3/devices"
#define SENSOR_PATH   		"/sys/class/msensor"
#define MAX_RESPONSE_LENGTH 	64
#define MAX_NUM_OF_RESPONSES 	4

/*
 * Function to send a Linux shell command and return the number of
 * responses it got, up to a maximum of MAX_NUM_OF_RESPONSES
 *
 */
int SendShellCommand (string Command, char* Response)
{
  FILE *f;
  int i=0;
  char cResponse[MAX_RESPONSE_LENGTH];

  // Execute a shell command and open a pipe to read the results
  if (!(f = popen(Command.c_str(),"r")))
    {
      cout << "Error in Ev3Device::SendShellCommand: " << Command << endl;
      exit (-1);
    }

  // Keep reading the pipe and concatenate the read strings
  while((fgets(cResponse,MAX_RESPONSE_LENGTH,f)!=NULL) &&
         (i<MAX_NUM_OF_RESPONSES)){
      // Strip <LF> if present in response
      if ((cResponse[strlen(cResponse)-1])==10) {
	cResponse[strlen(cResponse)-1]='\0';
      }
      strncpy(Response+i*MAX_RESPONSE_LENGTH,cResponse,MAX_RESPONSE_LENGTH);
      ++i;
  }
  pclose(f);
  return i;
}

/*
 * Ev3Device constructor.
 *
 * It allows to create any EV3 component (motor or sensor) and get its
 * file path on ev3dev filesystem for further addressing
 *
 */
Ev3Device::Ev3Device (Port_t Port, DataLogger* Logger)
{
  m_DevicePath=GetDevicePath(Port);
  m_DeviceID=" EV3DEVICE:"+sPortName[Port];
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
  string sCommand;
  string sFilePath;
  string sOutPort;
  int nNumResponses;

  char cResponses[MAX_RESPONSE_LENGTH*MAX_NUM_OF_RESPONSES];
  char cResponse[MAX_RESPONSE_LENGTH];

  switch (Port) {
    case IN_1:
    case IN_2:
    case IN_3:
    case IN_4:
      // Assuming only sensors are attached to IN ports, do a 'ls'
      // on SENSOR_PATH to get the different 'sensorN' values
      sCommand=string("ls ")+SENSOR_PATH;
      nNumResponses=SendShellCommand(sCommand,cResponses);
      // For each 'sensorN', determine whether it is attached to the
      // port whose DevicePath wants to be determined
      for(int i=0;i<nNumResponses;++i){
	  sCommand=string("cat ")+SENSOR_PATH+string("/")
	                         +string(cResponses+i*MAX_RESPONSE_LENGTH)
	                         +string("/port_name");
	  SendShellCommand(sCommand,cResponse);
	  // If the name of the port is in its "port_name" property,
	  // sensor path search is over
	  if(string(cResponse)==sPortName[Port]){
	      sFilePath=SENSOR_PATH
		              +string("/")
		              +string(cResponses+i*MAX_RESPONSE_LENGTH);
	      Trace(m_Logger,EV3DEVICE_DBG_LVL,m_DeviceID+"-> Got file path:"
	            +sFilePath);
	      return sFilePath;
	  }
      }
      // Log error condition, terminate logger and exit program
      Trace(m_Logger,EV3DEVICE_DBG_LVL,m_DeviceID+
            " ***ERROR*** No sensor found in port ");
      m_Logger->~DataLogger();
      exit(-1);
      break;
    case OUT_A:
    case OUT_B:
    case OUT_C:
    case OUT_D:
      sOutPort="/"+sPortName[Port]+"/"+sPortName[Port]+
               ":ev3-tacho-motor/tacho-motor/";
      sCommand=string("ls ")+MOTOR_PATH+sOutPort;
      SendShellCommand(sCommand,cResponse);
      sFilePath=MOTOR_PATH+sOutPort+string(cResponse);
      Trace(m_Logger,EV3DEVICE_DBG_LVL,m_DeviceID+"-> Got file path:"
      	            +sFilePath);
      return sFilePath;
      break;
    default:
      break;
  }
  // Log error condition, terminate logger and exit program
  Trace(m_Logger,EV3DEVICE_DBG_LVL,m_DeviceID+
	" ***ERROR*** Attempting to attach device to unknown port");
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





