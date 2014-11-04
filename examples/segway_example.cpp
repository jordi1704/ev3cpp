/*
 * main.cpp
 *
 *  Created on: Oct 15, 2014
 *      Author: jordi
 */

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "cutils.h"
#include <stdio.h>
#include <unistd.h>


#include "Tacho.h"
#include "Touch.h"
#include "Gyro.h"
#include "globalDefs.h"
#include "DataLogger.h"

#include <thread>

using namespace std;

float Kp=3.0;
float Kd=1.5;


int Rate, Angle;
int Power;
int Error;
Tacho* myMotor;
DataLogger* Logger;

void setPID()
{
  float p,d;
  char KeyStroke;
  system ("/bin/stty raw");
  while(true){
    KeyStroke=getchar();
    switch (KeyStroke) {
      case 's':
	Kp=Kp+0.1;
	break;
      case 'a':
	Kp=Kp-0.1;
	break;
      case 'w':
	Kd=Kd+0.1;
	break;
      case 'q':
	Kd=Kd-0.1;
	break;
      default:
	break;
    }
    cout << "Kp: " << Kp << endl;
    cout << "Kd: " << Kd << endl;
  }
}

void EmergencyExit()
{
  Touch* myButton=new Touch(IN_4,NULL);
  while(1){
  if(myButton->IsPressed())
    {
      // stop motors, restore linux console mode and close logging
      myMotor->Stop();
      system ("/bin/stty cooked");
      Logger->~DataLogger();
      exit(0);
    }
  }
}

void TraceGen()
{
  while(1){
    std::stringstream msg;
    msg << Error <<","<<Rate<<","<<Power<<","<<Kp<<","<<Kd<<endl;
    string Message=msg.str();
    Trace(Logger,DBG_LVL_3,"->PID params: "+Message);
    usleep(ONE_MILLISECOND*200);
  }
}

int main()
{
  Logger=new DataLogger(EV3_LOG_FILE,DBG_LVL_3);

  Gyro*  myGyro=new Gyro(IN_3,ANGLE_AND_RATE,Logger);
  myMotor=new Tacho(OUT_A,Logger);

  myGyro->GetRateAndAngle(Rate,Angle);
  int initAngle=Angle;
  myMotor->RunForever(0);

  thread t1(setPID);
  thread t2(TraceGen);
  thread t3(EmergencyExit);

  while(1){
      myGyro->GetRateAndAngle(Rate,Angle);
      Error = Angle-initAngle;
      Power=Kp*Error+Kd*Rate;
      myMotor->SetSpeed(Power);


  }
  exit(0);
}



