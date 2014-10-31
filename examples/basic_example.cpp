
#include "Tacho.h"
#include "Touch.h"
#include "Color.h"


int main()
{
  // Create a data logger to dump activity traces over 'ev3.log' file
  DataLogger* myLogger=new DataLogger("ev3.log",DBG_LVL_0);

  // Create a tacho motor connected on output port A and get traces
  Tacho* myMotor=new Tacho(OUT_A,myLogger);

  // Create a light sensor on input port 3 and get traces
  LightSensor* myLightSensor=new LightSensor(IN_3,myLogger);

  // Create a touch sensor on input port 4. As no logger pointer is specified,
  // there will be no logged info about touch sensor
  Touch* myTouch=new Touch(IN_4);

  // Start motor at power 50%
  myMotor->RunForever(50);

  // Wait until touch sensor is pressed or room light is off to stop the motor
  while(!myTouch->IsPressed() && (myLightSensor->GetAmbient()!=0));

  // Stop the motor
  myMotor->Stop();

  return(0);
}



