// -*- mode: C++; coding: utf-8 -*-

#ifndef __MessageI_h__
#define __MessageI_h__

#include <Message.h>

namespace UCLM {

  class MessageI : virtual public Message {
  public:

    MessageI(::std::string);

    virtual void write(const ::std::string&,
                       const Ice::Current&);

    virtual ::std::string read(const Ice::Current&);

  private:  
    ::std::string message;
  };
}

#endif // __MessageI_h__
