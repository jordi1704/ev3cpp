/*
 * Touch.h
 *
 *  Created on: Oct 5, 2014
 *      Author: jordi
 */

#ifndef TOUCH_H_
#define TOUCH_H_

#include "Sensor.h"

#define TOUCH_STATE   "value0"
#define TOUCH_PRESSED "1"

using namespace std;

class Touch : public Sensor
{
private:
public:
  bool IsPressed();
  Touch (Port_t Port, DataLogger* Logger=NULL);
  virtual
  ~Touch ();
};

#endif /* TOUCH_H_ */
