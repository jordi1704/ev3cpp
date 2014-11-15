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

namespace dirIO
{

enum io_t {IN, OUT};

class DirectIO
{
public:
  DirectIO (io_t IO, string Channel);
  virtual
  ~DirectIO ();
  ofstream* m_obuf;
  ifstream* m_ibuf;
  void SendData (string Data);
  void GetData(string &Data);
private:
  io_t m_IOMode;
};
}




#endif /* DIRECTIO_H_ */
