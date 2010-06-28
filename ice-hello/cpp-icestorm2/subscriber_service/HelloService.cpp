#include <Ice/Application.h>
#include <IceStorm/IceStorm.h>
#include <IceUtil/UUID.h>

#include <Ice/Ice.h>
#include <Ice/Application.h>
#include "helloI.h"
#include <HelloService.h>


using namespace std;
using namespace UCLM;

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

  /*
  _adapter = communicator->createObjectAdapter(name);
  ::Ice::ObjectPtr object = new UCLM::HelloI;
  _adapter->add(object, ::Ice::stringToIdentity("ServiceHola"));
  _adapter->activate();*/

  // Ice::ObjectPrx base = communicator->stringToProxy("IceStorm/TopicManager:tcp -p 9996:udp -p 9996");
  Ice::PropertiesPtr properties = communicator->getProperties();

  const string proxyProperty = "IceStorm.TopicManager.Proxy";
  string proxy = properties->getProperty(proxyProperty);
  Ice::ObjectPrx base = communicator->stringToProxy(proxy);
  IceStorm::TopicManagerPrx manager = IceStorm::TopicManagerPrx::checkedCast(base);


  // Set the requested quality of service "reliability" =
  // "batch". This tells IceStorm to send events to the subscriber
  // in batches at regular intervals.
  //
  IceStorm::QoS qos;
  qos["reliability"] = "batch";
  
  //
  // Create the servant to receive the events.
  //
  Ice::ObjectAdapterPtr adapter = communicator->createObjectAdapter("Hello.Subscriber");
  Ice::ObjectPtr helloObj = new HelloI;

  //
  // List of all subscribers.
  //
  map<string, Ice::ObjectPrx> subscribers;

  // Creación de Objeto con faceta.
  Ice::ObjectPrx object = adapter->addFacetWithUUID(helloObj,"hola");
  // Creación de Objeto sin faceta
  //Ice::ObjectPrx object = adapter->addWithUUID(helloObj);

  IceStorm::TopicPrx topic = manager->retrieve("HelloWorld");
  topic->subscribe(qos, object);
  
  
  
  adapter->activate();
  communicator->waitForShutdown();

  topic->unsubscribe(object);
  
  cout << "** Activación del Servicio." << endl;
  cout << object << endl;


}

void
HelloService::stop()
{
  _adapter->deactivate();
  cout << "** Desactivación del Servicio" << endl;
}
