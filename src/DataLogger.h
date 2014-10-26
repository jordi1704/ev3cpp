/*
 * DataLogger.h
 *
 *  Created on: Oct 25, 2014
 *      Author: jordi
 */

#ifndef DATALOGGER_H_
#define DATALOGGER_H_

#include <fstream>
#include <stdlib.h>

using namespace std;

enum DbgLevel_t {DBG_LVL_0, DBG_LVL_1, DBG_LVL_2, DBG_LVL_3, NO_DBG} ;

class DataLogger {
public:
  DataLogger(string FileName, DbgLevel_t DbgLevel);
  virtual ~DataLogger();
  void LogMessage(DbgLevel_t DbgLevel, std::string Msg);
private:
  ofstream m_obuf;
  DbgLevel_t m_DbgLevel;
};

void Trace(DataLogger* Logger, DbgLevel_t DbgLevel, string Msg);

#endif /* DATALOGGER_H_ */
