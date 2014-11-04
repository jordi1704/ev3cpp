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

class Led
{
public:
  Led (LedPosition_t LedPosition, LedColor_t LedColor);
  virtual
  ~Led ();
  void SetLedColor(LedPosition_t LedPosition, LedColor_t LedColor);
  LedPosition_t m_LedPosition;
  LedColor_t m_LedColor;
  string m_LedPath;
};

#endif /* LED_H_ */
