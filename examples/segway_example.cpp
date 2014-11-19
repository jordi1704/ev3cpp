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

float Kp=15.0f;
float Kd=1.0f;
float Ki=2.5f;
float Kpos=0.2f;
float deltaT=0.2;
float Offset=18.0f;

// 40 20 3 molt be
// 30 10 5
// 100 10 5

bool End = false;

bool t1s,t2s,t3s;


int Rate, Angle;
int Power;
int Error;
float acError=0;
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
      delete myButton;
      End=true;
    }
    if(End){
	t2s=false;
	break;
    }
    //cout << "monitoring button" << endl;
    usleep(ONE_SECOND);
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
  cout << "One" << endl;

  ServoGyro*  myGyro=new ServoGyro(IN_2);
  MotorL=new ServoMotor(OUT_A);
  MotorR=new ServoMotor(OUT_B);

  cout << "Two" << endl;

  myGyro->GetRateAndAngle(Rate,Angle);
  int initPosition=MotorL->GetPosition();
  int initAngle=Angle;
  MotorL->RunForever(0);
  MotorR->RunForever(0);
  usleep(ONE_SECOND);

  int Position;
  int ErrorPos;
  thread t3(EmergencyExit);



  while(1){
      //start=clock();
      myGyro->GetRateAndAngle(Rate,Angle);
      //cout << "Angle: " << ToString(Angle) << " Rate: "<< ToString(Rate) << endl;
      Position=MotorL->GetPosition();
      Error = Angle-initAngle+Offset;
      acError=acError+Error*deltaT;
      ErrorPos=Position-initPosition;
      //cout << "Error Pos: " << ToString(ErrorPos)<<endl;
      //cout << "Error Angle: " << ToString(Error) << endl;
      //cout << "acError = " << ToString(acError)<< endl;
      Power=Kp*Error+Kd*Rate+Ki*acError+Kpos*ErrorPos;
      if ((Error<=1)&&(Error>=-1)) {
	  Power=0;
	  acError=0;
      }
      if (Power>100) Power=100;
      if (Power<-100) Power= -100;
      //cout << "Power: "<< ToString(Power) << endl;

      //cout << "Setting speed to motors: " << ToString(Power)<<endl;
      MotorL->SetSpeed(Power);
      MotorR->SetSpeed(Power);
      //cout << "Speed updated " << endl;
      //cout << "Duration of MotorR speed update is: " << ToString((clock()-start)*1000000.0f/717197.0f) <<" microseconds"<< endl;

      if ((!t2s)) break;
  }

  cout << "Three" << endl;
  MotorL->Stop();
  MotorR->Stop();
  cout << "Four" << endl;

  delete MotorL;
  cout << "Five" << endl;
  delete MotorR;
  cout << "Six" << endl;
  delete myGyro;
  cout << "Seven" << endl;

  exit(0);
}



