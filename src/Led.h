/*
 * Led.h
 *
 *  Created on: Nov 4, 2014
 *      Author: jordi
 */

#ifndef LED_H_
#define LED_H_

#include <Ev3Device.h>

class Led : public Ev3Device
{
public:
  Led ();
  virtual
  ~Led ();
};

#endif /* LED_H_ */
