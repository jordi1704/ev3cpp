#include "DataLogger.h"
#include <iostream>
#include <ctime>

using namespace std;

DataLogger::DataLogger(string Filename, DbgLevel_t DbgLevel=NO_DBG)
{
  m_obuf.open(Filename.c_str(),ios::out);
  if(!m_obuf)
  {
    cout << "Error opening " << Filename << endl;
    exit(1);
  }
  m_DbgLevel=DbgLevel;
}

DataLogger::~DataLogger()
{
  m_obuf.close();
}

void Trace(DataLogger* Logger, DbgLevel_t DbgLevel, string Msg)
{
  if(Logger){
      Logger->LogMessage(DbgLevel,Msg);
  }
}

void DataLogger::LogMessage(DbgLevel_t DbgLevel, string Msg)
{
  char buffer[80];
  time_t LogTime;
  struct tm *timeinfo;
  if(DbgLevel>=m_DbgLevel){
    time(&LogTime);
    timeinfo=localtime(&LogTime);
    // Separate date & time with comma for further analysis on Excel using
    // CSV format
    strftime(buffer,80,"%d-%m-%Y,%I:%M:%S,",timeinfo);
    m_obuf << string(buffer) << Msg << endl;
  }
}


