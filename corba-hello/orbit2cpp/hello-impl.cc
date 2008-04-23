#include <iostream>
#include "hello-impl.hh"

using namespace std;

void 
SENDA::hello_impl::puts(char const *str) throw (CORBA::SystemException)
{
  cout << "Servidor Hello ORBit2Cpp:" << endl;
	cout << str << endl; 
}
