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
#include <vector>



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
      if(Mode==sAllowedMode) {
	  IODevice::WritePropertyFile(m_DevicePath+"/mode",Mode);
      return;
      }
  }
  // If wrong mode set, disconnect sensor
  cout << "Error seting mode " << Mode << endl;
  m_Connected=false;
  exit(-1);
}

bool Sensor::Connect(Port_t Port, const string Types[], const int NumTypes)
{
  DIR *Directory;
  struct dirent* DirectoryEntry;
  string sDeviceType="sensor";
  const string sDevicePath=SENSOR_PATH;
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
	    if (m_TypeName.find(Types[i])!=std::string::npos) {
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
}



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
}

Touch::~Touch (){};

void Touch::InitSensor()
{
  Sensor::SetMode("TOUCH");
}

bool Touch::IsPressed()
{
  return (Sensor::GetValue(0)==1);
}

Gyro::Gyro(Port_t Port) : Sensor(Port,&sEv3Sensor[EV3_GYRO_SENSOR],1)
{
  this->InitSensor();
}

Gyro::~Gyro (){}

void Gyro::InitSensor()
{
  Sensor::SetMode("GYRO-RATE");
}

short int Gyro::GetRotationalSpeed()
{
  return Sensor::GetValue(0);
}

Motor::Motor(Port_t Port, const string Type) : IODevice(Port)
{
  string* sSupportedMotorTypes;

  int nNumOfSupportedMotorTypes;
  if(Type==""){
      sSupportedMotorTypes=new string[NUM_OF_SUPPORTED_MOTORS];
      for (int i = 0; i < NUM_OF_SUPPORTED_MOTORS; ++i) {
	sSupportedMotorTypes[i]=sEv3Motor[i];
      }
      nNumOfSupportedMotorTypes=NUM_OF_SUPPORTED_MOTORS;
  } else {
      sSupportedMotorTypes=new string;
      *sSupportedMotorTypes=Type;
      nNumOfSupportedMotorTypes=1;
  }
  m_Connected=this->Connect(Port,sSupportedMotorTypes,nNumOfSupportedMotorTypes);
  delete [] sSupportedMotorTypes;
  if (m_Connected){
      m_DutyCycle=atoi(ReadPropertyFile(m_DevicePath+"/duty_cycle").c_str());
      m_DutyCycleSP=atoi(ReadPropertyFile(m_DevicePath+"/duty_cycle_sp").c_str());
      m_Position=atoi(ReadPropertyFile(m_DevicePath+"/position").c_str());
      m_PositionMode=ReadPropertyFile(m_DevicePath+"/position_mode");
      m_PositionSP=atoi(ReadPropertyFile(m_DevicePath+"/position_sp").c_str());
      m_PulsesPerSecond=atoi(ReadPropertyFile(m_DevicePath+"/pulses_per_second").c_str());
      m_PulsesPerSecondSP=atoi(ReadPropertyFile(m_DevicePath+"/pulses_per_second_sp").c_str());
      m_RampUpSP=atoi(ReadPropertyFile(m_DevicePath+"/ramp_up_sp").c_str());
      m_RampDownSP=atoi(ReadPropertyFile(m_DevicePath+"/ramp_down_sp").c_str());
      m_RegulationMode=ReadPropertyFile(m_DevicePath+"/regulation_mode");
      m_Run=atoi(ReadPropertyFile(m_DevicePath+"/run").c_str());
      m_RunMode=ReadPropertyFile(m_DevicePath+"/run_mode");
      m_SpeedRegulationP=atoi(ReadPropertyFile(m_DevicePath+"/speed_regulation_P").c_str());
      m_SpeedRegulationI=atoi(ReadPropertyFile(m_DevicePath+"/speed_regulation_I").c_str());
      m_SpeedRegulationK=atoi(ReadPropertyFile(m_DevicePath+"/speed_regulation_K").c_str());
      m_SpeedRegulationD=atoi(ReadPropertyFile(m_DevicePath+"/speed_regulation_D").c_str());
      m_State=ReadPropertyFile(m_DevicePath+"/state");
      m_StopMode=ReadPropertyFile(m_DevicePath+"/stop_mode");
      string sAllowedModes=ReadPropertyFile(m_DevicePath+"/stop_modes");
      stringstream ssModes(sAllowedModes);
      string sMode;
      vector<string> str;
      while(ssModes >> sMode){
	 str.push_back(sMode);
      }
      m_StopModes=new string[str.size()];
      for (int i = 0; i < str.size(); ++i) {
	m_StopModes[i]=str[i];
      }
      m_TimeSP=atoi(ReadPropertyFile(m_DevicePath+"/time_sp").c_str());
  }
}

Motor::~Motor()
{
  delete [] m_StopModes;
}

bool Motor::Connect(Port_t Port, const string Types[], const int NumTypes)
{
  DIR *Directory;
  struct dirent* DirectoryEntry;
  string sDeviceType="tacho-motor";
  const string sDevicePath=MOTOR_PATH;
  string sOutputPort;
  string sMotorType;

  Directory=opendir(sDevicePath.c_str());

  // Enumerate devices
  while((DirectoryEntry=readdir(Directory))!=NULL){

      if(strstr(DirectoryEntry->d_name,sDeviceType.c_str())){

	  // Store file path
	  m_DevicePath=sDevicePath+string(DirectoryEntry->d_name);

	  //Determine port
	  m_PortName=ReadPropertyFile(m_DevicePath+"/port_name");

	  // Determine motor type
	  m_Type=ReadPropertyFile(m_DevicePath+"/type");

	  // Match motor port and type
	  for (int i = 0; i < NumTypes; ++i) {
	    if (m_Type.find(Types[i])!=std::string::npos) {
		switch (Port) {
		  case OUTPUT_AUTO:
		    for (int port = OUTPUT_A; port <= OUTPUT_D; ++port) {
			if(m_PortName==sPort[port]){
			    m_DeviceIndex=port;
			}
		    }
		    cout << "Connected type " << m_Type << " on " << m_PortName<< endl;
		    return true;
		    break;
		  case OUTPUT_A:
		  case OUTPUT_B:
		  case OUTPUT_C:
		  case OUTPUT_D:
		    if(m_PortName==sPort[Port]){
			m_DeviceIndex=Port;
			cout << "Connected type " << m_Type << " on " << m_PortName<< endl;
			return true;
		    } else {
			cout << "Motor is available but not connected to " << sPort[Port] << endl;
			return false;
		    }
		  default:
		    cout << "Motor can only be connected to output port" << endl;
		    return false;
		    break;
		}
	    }
	  }
      } // end find motor
  } // end while
  cout << "unable to find any motor of allowed types" << endl;
  return false;
}

void Motor::Reset()
{
  this->WritePropertyFile("reset","1");
}
