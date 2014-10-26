/*
 * MiniTacho.cpp
 *
 *  Created on: Oct 12, 2014
 *      Author: jordi
 */

#include "MiniTacho.h"
#include <iostream>
#include "cutils.h"


MiniTacho::MiniTacho(Port_t Port,DataLogger* Logger) : Motor(Port,Logger)
{
  cout << "Constructed Mini-tacho motor on port " << sPortName[Port] << endl;
}


MiniTacho::~MiniTacho ()
{
}

int MiniTacho::CalculateSpeed(Power_t Power){
  return (Power*MAX_SPEED_SMALL_MOTOR)/100;
}



