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

float Kp=40.0f;
float Kd=2.0f;
float Offset=2.0f;

// 40 20 3 molt be
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
      delete myButton;
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

//TODO perque es loga la creacio del motor pair si te null al logger?
// TODO perque no actua el pulsador? Si que actua pero els motors queden al seu rotllo
//TODO els motors van descompensats

int main()
{
  t2s=true;
  //Logger=new DataLogger(EV3_LOG_FILE,DBG_LVL_0);

  ServoGyro*  myGyro=new ServoGyro(IN_2);
  MotorL=new ServoMotor(OUT_A);
  MotorR=new ServoMotor(OUT_B);


  myGyro->GetRateAndAngle(Rate,Angle);
  int initAngle=Angle;
  MotorL->RunForever(0);
  MotorR->RunForever(0);
  usleep(ONE_SECOND);


  thread t3(EmergencyExit);



  while(1){
      //start=clock();
      myGyro->GetRateAndAngle(Rate,Angle);
      //cout << "Angle: " << ToString(Angle) << " Rate: "<< ToString(Rate) << endl;

      Error = Angle-initAngle+Offset;
      Power=Kp*Error+Kd*Rate;
      if (Power>100) Power=100;
      if (Power<-100) Power= -100;

      //cout << "Setting speed to motors: " << ToString(Power)<<endl;
      MotorL->SetSpeed(Power);
      MotorR->SetSpeed(Power);
      //cout << "Speed updated " << endl;
      //cout << "Duration of MotorR speed update is: " << ToString((clock()-start)*1000000.0f/717197.0f) <<" microseconds"<< endl;

      if ((!t2s)) break;
  }

  MotorL->Stop();
  MotorR->Stop();


  delete MotorL;
  delete MotorR;
  delete myGyro;

  exit(0);
}



