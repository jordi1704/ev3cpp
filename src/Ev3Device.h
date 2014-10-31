/*
 * Ev3Device.h
 *
 *  Created on: Oct 12, 2014
 *      Author: jordi
 */

#ifndef EV3DEVICE_H_
#define EV3DEVICE_H_

#include "DataLogger.h"

enum Port_t {  IN_1,  IN_2,  IN_3,  IN_4,
              OUT_A, OUT_B, OUT_C, OUT_D, _PORTS_NUM_ };

const string sPortName[_PORTS_NUM_]={  "in1", "in2", "in3", "in4",
				      "outA","outB","outC","outD" };

const DbgLevel_t EV3DEVICE_DBG_LVL    = DBG_LVL_0;
const DbgLevel_t MOTOR_DBG_LVL        = DBG_LVL_1;
const DbgLevel_t SENSOR_DBG_LVL	      = DBG_LVL_1;
const DbgLevel_t TACHO_DBG_LVL        = DBG_LVL_2;
const DbgLevel_t MINITACHO_DBG_LVL    = DBG_LVL_2;
const DbgLevel_t TOUCH_DBG_LVL        = DBG_LVL_2;
const DbgLevel_t GYRO_DBG_LVL         = DBG_LVL_2;
const DbgLevel_t COLOR_DBG_LVL        = DBG_LVL_2;
const DbgLevel_t COLORIMETER_DBG_LVL  = DBG_LVL_3;
const DbgLevel_t LIGHTSENSOR_DBG_LVL  = DBG_LVL_3;


class Ev3Device
{
public:
  Ev3Device (Port_t Port, DataLogger* Logger=NULL);
  virtual
  ~Ev3Device ();
  void SetDeviceParameter(string Parameter, string Value);
  string GetDeviceParameter(string Parameter);
  string m_DeviceID;    // Name and Port of the device
  DataLogger* m_Logger;
private:
  string m_DevicePath;  // Path of the device in ev3dev filesystem
  string GetDevicePath(Port_t Port);
};

#endif /* EV3DEVICE_H_ */
