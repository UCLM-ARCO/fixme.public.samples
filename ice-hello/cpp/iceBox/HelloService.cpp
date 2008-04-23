#include <Ice/Ice.h>
#include <Ice/Application.h>
#include "helloI.h"
#include <HelloService.h>
using namespace std;

extern "C"
{

//
// Factory function
//
HELLO_API ::IceBox::Service*
create(::Ice::CommunicatorPtr communicator)
{
    return new HelloService;
}
 
}

HelloService::HelloService(){}
HelloService::~HelloService() {}

int cont = 0;

void
HelloService::start(const string& name,
	     const ::Ice::CommunicatorPtr& communicator,
	     const ::Ice::StringSeq& args)
{

  _adapter = communicator->createObjectAdapter(name);
  ::Ice::ObjectPtr object = new UCLM::HelloI;
  _adapter->add(object, communicator->stringToIdentity("ServiceHola"));
  _adapter->activate();

  cout << "** Activación del Servicio." << endl;
  cout << object << endl;


}

void
HelloService::stop()
{
  _adapter->deactivate();
  cout << "** Desactivación del Servicio" << endl;
}
