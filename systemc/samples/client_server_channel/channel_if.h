#ifndef CHANNEL_IF_H
#define CHANNEL_IF_H


#include "systemc.h"

class channel_read: virtual public sc_interface
{
public:
  virtual bool ch_read() = 0;
};

class channel_write: virtual public sc_interface
{
public:
  virtual void ch_write(bool b) = 0;
};

#endif
