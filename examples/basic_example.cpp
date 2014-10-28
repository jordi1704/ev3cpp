
#include "Tacho.h"
#include "Touch.h"

int main()
{

  // Create a tacho motor connected on output port A
  Tacho* myMotor=new Tacho(OUT_A);

  // Create a touch sensor on input port 4
  Touch* myTouch=new Touch(IN_4);

  // Start motor at 50% of its power
  myMotor->RunForever(50);

  // Wait until touch sensor is pressed to stop the motor
  while(!myTouch->IsPressed());

  // Stop the motor
  myMotor->Stop();

  return(0);

}



