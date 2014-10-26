/*
 * cutils.cpp
 *
 *  Created on: Oct 4, 2014
 *      Author: jordi
 */
#include <sstream>
//#include <iostream>
//#include <ctime>
//#include <stdlib.h>
//#include <fstream>
//#include <assert.h>
#include "cutils.h"

#define MILLISEC_LOOP_ITERATIONS 11390


using namespace std;


string ToString(int Value)
{
  stringstream ss;
  ss << Value;
  return (ss.str());
}

void msWait (int ms){
  for(int i=0;i<ms*MILLISEC_LOOP_ITERATIONS;i++);
}





