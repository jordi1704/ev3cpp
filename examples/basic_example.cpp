
#include "IODevice.h"
#include "cutils.h"

#include <iostream>
#include <string.h>
#include <stdlib.h>

int main()
{

Touch* myTouch=new Touch();
Motor* myMotor=new Motor();
time_t start,end;

start=clock();
WaitForMilliseconds(1000);
end=clock();
cout << to_string((end-start)/675547.0f*1000000)<<endl;


//while(0){
//    start=clock();
//    if(myTouch->IsPressed()) {
//	end=clock();
//	cout << to_string((end-start)/675356.0f*1000000)<<endl;
//	cout << "Pressed"<<endl;
//    } else {
//	end=clock();
//	cout << to_string((end-start)/675356.0f*1000000)<<endl;
//	cout << "Released"<<endl;
//
//    }
//}



  return(0);
}



