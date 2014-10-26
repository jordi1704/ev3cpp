/*
 * cutils.cpp
 *
 *  Created on: Oct 4, 2014
 *      Author: jordi
 */
#include <sstream>
#include "cutils.h"

#define MILLISEC_LOOP_ITERATIONS 11390


std::string ToString(int Value)
{
  std::stringstream ss;
  ss << Value;
  return (ss.str());
}

void WaitForMilliseconds (int ms){
  for(int i=0;i<ms*MILLISEC_LOOP_ITERATIONS;i++);
}





