/*
 * Led.h
 *
 *  Created on: Nov 4, 2014
 *      Author: jordi
 */

#ifndef LED_H_
#define LED_H_

#include <Ev3Device.h>

enum LedPosition_t {LEFT, RIGHT};
enum LedColor_t {RED, GREEN};


class Led : public Ev3Device
{
public:
  Led (Port_t Port, DataLogger* Logger=NULL);
  virtual
  ~Led ();
};

#endif /* LED_H_ */
