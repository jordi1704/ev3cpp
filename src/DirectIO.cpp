/*
 * DirectIO.cpp
 *
 *  Created on: Nov 13, 2014
 *      Author: jordi
 */

#include <DirectIO.h>

namespace dirIO
{

DirectIO::DirectIO(io_t IO, string Channel)
{
  if (IO==OUT) {
    m_obuf=new ofstream(Channel.c_str(),ios::out);
  } else {
    m_ibuf=new ifstream(Channel.c_str(),ios::in);
  }
  m_IOMode=IO;
}

DirectIO::~DirectIO ()
{
  if(m_IOMode==OUT){
      m_obuf->close();
      delete m_obuf;
  }else {
      m_ibuf->close();
      delete m_ibuf;
  }
}

void DirectIO::SendData(string Data)
{
  *m_obuf << Data;
  m_obuf->flush();
}

void DirectIO::GetData(string &Data)
{
  getline(*m_ibuf,Data);
}

}
