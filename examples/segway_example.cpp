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
#include <ctime>
#include "Motor.h"

#include <thread>

using namespace std;

float Kp=20.0f;
float Kd=5.0f;
float Offset=10.0f;

// 20 5 3 molt be
// 30 10 5
// 100 10 5

bool End = false;

bool t1s,t2s,t3s;

int Rate, Angle;
int Power;
int Error;
DataLogger* Logger;

ServoMotor* MotorL;
ServoMotor* MotorR;

clock_t start, end, duration;



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
      MotorL->Stop();
      MotorR->Stop();
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
  //Logger=new DataLogger(EV3_LOG_FILE,DBG_LVL_0);
  cout << "One bis" << endl;
  //Touch* myButton=new Touch(IN_3);

  Gyro*  myGyro=new Gyro(IN_2,ANGLE_AND_RATE);

  cout << "Two" << endl;
  MotorL=new ServoMotor(OUT_A);
  MotorR=new ServoMotor(OUT_B);
  cout << "Three" << endl;
  myGyro->GetRateAndAngle(Rate,Angle);
  int initAngle=Angle;
  MotorL->RunForever(0);
  MotorR->RunForever(0);

  //thread t1(setPID);
  //thread t2(TraceGen);
  thread t3(EmergencyExit);

  while(1){
//      start=clock();
//      WaitForMilliseconds(2000);
//      cout << "Duration is: " << ToString((clock()-start)*1000000.0f/717197.0f) <<" microseconds"<< endl;
//      break;
      start=clock();
      myGyro->GetRateAndAngle(Rate,Angle);
      Error = Angle-initAngle+Offset;
      Power=Kp*Error+Kd*Rate;
      if (Power>100) Power=100;
      if (Power<-100) Power= -100;
      MotorL->SetSpeed(Power);
      MotorR->SetSpeed(Power);
      cout << "Duration is: " << ToString((clock()-start)*1000000.0f/717197.0f) <<" microseconds"<< endl;
      //usleep(1000*ONE_MILLISECOND);
      if ((!t2s)) break;
  }
  MotorL->Stop();
  MotorR->Stop();
  //t1.~thread();
  exit(0);
}



