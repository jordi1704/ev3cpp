/*
 * DirectIO.h
 *
 *  Created on: Nov 13, 2014
 *      Author: jordi
 */

#ifndef DIRECTIO_H_
#define DIRECTIO_H_

#include <string.h>
#include <fstream>

using namespace std;

class FileIOChannel
{
public:
  FileIOChannel (string Channel);
  virtual
  ~FileIOChannel ();
  void SendData (string Data, bool LeaveOpen=false);
  void GetData(string &Data);
  ofstream* m_obuf;
  ifstream* m_ibuf;
private:
  char* m_Channel;
};

class InputChannels
{
public:
  InputChannels(int NumOfChannels, string DevicePath);
  ~InputChannels();
  void GetData(int ChannelID, string &Data);
  int m_NumOfChannels;
private:
  FileIOChannel** m_Channels;
};



#endif /* DIRECTIO_H_ */
