/*
 * DirectIO.cpp
 *
 *  Created on: Nov 13, 2014
 *      Author: jordi
 */

#include <DirectIO.h>
#include "cutils.h"


namespace dirIO
{

DirectIO::DirectIO(io_t IO, string Channel)
{
  if (IO==OUT) {
    m_obuf=new ofstream();
    m_obuf->open(Channel.c_str(),ios::out);
  } else {
    m_ibuf=new ifstream();
  }
  m_IOMode=IO;
  m_Channel=new char[Channel.length()];
  strcpy(m_Channel,Channel.c_str());
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
  delete [] m_Channel;
}

void DirectIO::SendData(string Data)
{
  *m_obuf << Data;
  m_obuf->flush();
}

void DirectIO::GetData(string &Data)
{
  m_ibuf->open(m_Channel,ios::in);
  *m_ibuf >> Data;
  m_ibuf->close();
}
}

InputStreams::InputStreams(int NumOfChannels, string DevicePath)
{
  m_Channels=new dirIO::DirectIO*[NumOfChannels];
  for (int i = 0; i < NumOfChannels; ++i) {
    string st=DevicePath+"/value"+ToString(i);
    m_Channels[i]=new dirIO::DirectIO(dirIO::IN,st);
    }
  m_NumOfChannels=NumOfChannels;
}

InputStreams::~InputStreams()
{
  for (int i = 0; i < m_NumOfChannels ; ++i) {
    delete m_Channels[i];
  }
  delete [] m_Channels;
}

void InputStreams::GetData(int ChannelID, string &Data)
{
  this->InputStreams::m_Channels[ChannelID]->DirectIO::GetData(Data);
}

