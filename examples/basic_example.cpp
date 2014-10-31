
#include "Tacho.h"
#include "Touch.h"
#include "Color.h"

#include "globalDefs.h" //TODO remove after ONE_... not needed

#include <iostream> //TODO remove after cout

int main()
{
  // Create a data logger to dump activity traces over 'ev3.log' file
  DataLogger* myLogger=new DataLogger("ev3.log",DBG_LVL_0);

  // Create a tacho motor connected on output port A and get traces
  //Tacho* myMotor=new Tacho(OUT_A,myLogger);

  // Create a touch sensor on input port 4. As no logger pointer is specified,
  // there will be no logged info about touch sensor
  Touch* myTouch=new Touch(IN_4);

  LightSensor* myReflected=new LightSensor(IN_3,myLogger);

  // Start motor at power 50%
  //myMotor->RunForever(50);

  // Wait until touch sensor is pressed to stop the motor
  while(!myTouch->IsPressed()){
      cout << "Reflected value is: " << myReflected->GetReflected() << endl;
      usleep(ONE_SECOND);
      cout << "Ambient value is: " << myReflected->GetAmbient() << endl;
      usleep(ONE_SECOND);
  }

  cout << "Changing mode" << endl;

  myReflected->~LightSensor();

  Colorimeter* myColorimeter=new Colorimeter(IN_3,myLogger);
  string color;
  Color_t colordetected;
  usleep(5*ONE_SECOND);

  while(!myTouch->IsPressed()){
      colordetected=myColorimeter->GetColor();
      color=sColor[colordetected];
      cout << color <<endl;
      usleep(ONE_SECOND);
  }





  //TODO complete example

  // Stop the motor
  //myMotor->Stop();

  return(0);
}



