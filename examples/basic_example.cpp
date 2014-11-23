
#include "IODevice.h"
//#include "cutils.h"

#include <iostream>


int main()
{

Touch* myTouch=new Touch();

while(1){
    if(myTouch->IsPressed()) {
	cout << "Pressed"<<endl;
    } else cout << "Released"<<endl;
}



  return(0);
}



