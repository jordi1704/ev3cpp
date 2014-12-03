/*
 * cutils.cpp
 *
 *  Created on: Oct 4, 2014
 *      Author: jordi
 */
#include <sstream>
#include "cutils.h"

#define MILLISEC_LOOP_ITERATIONS 11390

void WaitForMilliseconds (int ms){
  for(int i=0;i<ms*MILLISEC_LOOP_ITERATIONS;i++);
}





