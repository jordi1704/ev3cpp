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

#include "Touch.h"
#include "Gyro.h"
#include "MotorPair.h"
#include "globalDefs.h"
#include "DataLogger.h"

#include <thread>

using namespace std;

float Kp=100.0f;
float Kd=100.0f;
float Offset=5.0f;

// 20 5 3 molt be
// 30 10 5
// 100 10 5

bool End = false;

bool t1s,t2s,t3s;

int Rate, Angle;
int Power;
int Error;
MotorPair* myMotor;
DataLogger* Logger;

void setPID()
{
  cout << "SetPID thread started"<< endl;
  t1s=true;
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
    if (End){
	t1s=false;
	break;
    }
  }
  cout << "SetPID thread ended" << endl;
}

void EmergencyExit()
{
  cout << "Emergency Exit thread started"<< endl;
  t2s=true;
  Touch* myButton=new Touch(IN_3,NULL);
  while(1){
  if(myButton->IsPressed())
    {
      // stop motors, restore linux console mode and close logging
      myMotor->Stop();
      system ("/bin/stty cooked");
      Logger->~DataLogger();
      End=true;
    }
    if(End){
	t2s=false;
	break;
    }
    //cout << "monitoring button" << endl;
    usleep(500*ONE_MILLISECOND);
  }
  cout << "Emergency Exit thread ended"<<endl;

}

void TraceGen()
{
  cout << "TraceGen thread started"<< endl;
  t3s=true;
  while(1){
    std::stringstream msg;
    msg << "PID Params,      "<<Error <<","<<Rate<<","<<Power<<","<<Kp<<","<<Kd;
    string Message=msg.str();
    //Trace(Logger,DBG_LVL_3,Message);
    usleep(ONE_MILLISECOND*200);
    if(End){
	Logger->~DataLogger();
	t3s=false;
	break;
    }
  }
  cout << "TraceGen thread ended"<< endl;
}
//TODO perque es loga la creacio del motor pair si te null al logger?
// TODO perque no actua el pulsador? Si que actua pero els motors queden al seu rotllo
//TODO els motors van descompensats

int main()
{
  cout << "One"<<endl;
  Logger=new DataLogger(EV3_LOG_FILE,DBG_LVL_3);

  //Touch* myButton=new Touch(IN_3);
  Gyro*  myGyro=new Gyro(IN_2,ANGLE_AND_RATE,Logger);
  cout << "Two" << endl;
  myMotor=new MotorPair(OUT_A,OUT_B,NULL);
  myMotor->SetRegulationMode(REG_OFF);
  cout << "Three" << endl;
  myGyro->GetRateAndAngle(Rate,Angle);
  int initAngle=Angle;
  myMotor->Straight(0);

  //thread t1(setPID);
  //thread t2(TraceGen);
  thread t3(EmergencyExit);

  while(1){
      myGyro->GetRateAndAngle(Rate,Angle);
      Error = Angle-initAngle+Offset;
      Power=Kp*Error+Kd*Rate;
      if (Power>100) Power=100;
      if (Power<-100) Power= -100;
      myMotor->Straight(Power);
      //usleep(100*ONE_MILLISECOND);
      if ((!t2s)&&(!t3s)) break;
  }
  myMotor->Stop();
  //t1.~thread();
  exit(0);
}



