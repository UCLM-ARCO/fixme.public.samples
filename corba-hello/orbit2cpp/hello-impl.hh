/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t;c-basic-offset: 4 -*- */
#ifndef _ORBIT_CPP_IDL_hello_IMPL_HH
#define _ORBIT_CPP_IDL_hello_IMPL_HH

#include "hello-cpp-skels.h"


namespace SENDA
{
	
class hello_impl : public POA_SENDA::hello {
public:
	void puts(char const *str) throw (CORBA::SystemException);
};

};


#endif
