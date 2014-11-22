
#include "IODevice.h"
#include "cutils.h"

#include <iostream>


int main()
{

  Sensor* Touch=new Sensor();

  if(Touch->m_Connected) {
      cout << "Connected with index " << ToString(Touch->m_DeviceIndex) << endl;
  } else {
      cout << "Not connected"<<endl;
  }

  return(0);
}



