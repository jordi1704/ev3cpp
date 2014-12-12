
#include "ev3cpp.h"
#include "cutils.h"

#include <iostream>
#include <string.h>
#include <stdlib.h>

int main()
{

  // Create a touch sensor
  Touch* myTouch=new Touch();

  // Create a motor
  ServoMotor* myMotor=new ServoMotor();

  // Set motor power to 50%
  myMotor->SetPower(50);

  // Wait until touch sensor is pressed
  while(!myTouch->IsPressed())
    {
      WaitForMilliseconds(100);
    }

  // Stop motor
  myMotor->SetPower(0);

  return(0);
}



