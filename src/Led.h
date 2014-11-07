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
enum LedColor_t {RED, GREEN, ORANGE, OFF, COLORS};
const string sLedColor[COLORS]={"red","green","orange","off"};


class LedMono : public Ev3Device
{
public:
  LedMono (Port_t Port, DataLogger* Logger=NULL);
  virtual
  ~LedMono ();
};

class Led
{
public:
  Led (LedPosition_t Position, DataLogger* Logger=NULL);
  virtual
  ~Led ();
  void SetColor(LedColor_t Color);
private:
LedMono* RedLed;
LedMono* GreenLed;
string m_DeviceID;
DataLogger* m_Logger;
};

#endif /* LED_H_ */
