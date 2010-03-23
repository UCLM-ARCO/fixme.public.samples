#ifndef __helloI_h__
#define __helloI_h__

#include <hello.h>

namespace UCLM
{

class HelloI : virtual public Hello
{
public:

  virtual void puts(const ::std::string&,
		    const Ice::Current&);
};

}

#endif
