/*
 * DirectIO.cpp
 *
 *  Created on: Nov 13, 2014
 *      Author: jordi
 */

#include <FileIOChannel.h>
#include <iostream>


FileIOChannel::FileIOChannel(string Channel)
{
  m_obuf=new ofstream();
  m_ibuf=new ifstream();
  m_Channel=new char[Channel.length()+1];
  if(!m_Channel || !m_obuf || !m_ibuf) {
      cout << "***ERROR*** Unable create FileIOChannel" << endl;
      exit(-1);
  }
  strcpy(m_Channel,Channel.c_str());
}

FileIOChannel::~FileIOChannel ()
{
  if (m_obuf->is_open()) m_obuf->close();
  if (m_ibuf->is_open()) m_ibuf->close();
  delete m_obuf;
  delete m_ibuf;
  delete [] m_Channel;
}

void FileIOChannel::SendData(string Data, bool LeaveOpen)
{
  if(!m_obuf->is_open()){
      m_obuf->open(m_Channel,ios::out);
      if(!m_obuf){
	  cout << "*** Error in SendData. Unable to open file" << endl;
	  exit(-1);
      }
  }
  *m_obuf << Data;
  m_obuf->flush();
  if(!LeaveOpen) m_obuf->close();
}

void FileIOChannel::GetData(string &Data)
{
  string sDest="";
  string sOrig="";
  m_ibuf->open(m_Channel,ios::in);
  *m_ibuf >> sDest;
  while(*m_ibuf >> sOrig){
      sDest=sDest+" "+sOrig;
  }
  Data=sDest;
  m_ibuf->close();
}


InputChannels::InputChannels(int NumOfChannels, string DevicePath)
{
  m_Channels=new FileIOChannel*[NumOfChannels];
  for (int i = 0; i < NumOfChannels; ++i) {
    string st=DevicePath+"/value"+to_string(i);
    m_Channels[i]=new FileIOChannel(st);
    }
  m_NumOfChannels=NumOfChannels;
}

InputChannels::~InputChannels()
{
  for (int i = 0; i < m_NumOfChannels ; ++i) {
    delete m_Channels[i];
  }
  delete [] m_Channels;
}

void InputChannels::GetData(int ChannelID, string &Data)
{
  this->InputChannels::m_Channels[ChannelID]->FileIOChannel::GetData(Data);
}

