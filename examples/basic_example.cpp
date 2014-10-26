
#include "Motor.h"
#include "Touch.h"

int main()
{
  // Create a tacho motor connected on output port A
  Motor* myMotor=new Motor(OUT_A);

  // Create a touch sensor on input port 2
  Touch* myTouch=new Touch(IN_2);

  // Start motor at 50% of its power
  myMotor->RunForever(50);

  // Wait until touch sensor is pressed to stop the motor
  while(!myTouch->IsPressed());

  return(0);

}



