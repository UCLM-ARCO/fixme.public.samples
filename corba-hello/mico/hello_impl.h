
#ifndef __HELLO_IMPL_H__
#define __HELLO_IMPL_H__

#include "hello.h"


// Implementation for interface hello
class hello_impl : virtual public POA_HelloModule::hello
{
  public:

    void puts( const char* str )
      throw(
        ::CORBA::SystemException)
    ;
};


#endif
