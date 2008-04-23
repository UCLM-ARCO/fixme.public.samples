#include <Ice/Ice.h>
#include <Ice/Application.h>
#include "helloI.h"

using namespace std;

class Server : public Ice::Application {
public:
  int
  run(int argc, char* args[]) {
	 shutdownOnInterrupt();

	 // objetos
	 Ice::CommunicatorPtr ic = communicator();

	 Ice::ObjectAdapterPtr adapter
		= ic->createObjectAdapter("Server");
	 Ice::ObjectPtr servant = new UCLM::HelloI;
	 cout << adapter->addFacet(servant,
			   ic->stringToIdentity("Hello"),
				   "hola") << endl;
	 Ice::ObjectPrx object = adapter->add(servant,
					      ic->stringToIdentity("Hello"));
	 adapter->activate();
	 cout << ic->proxyToString(object) << endl;
	 cout << object << endl;
	 
	 // Entrar en el bucle de eventos y esperar hasta finalizar
	 ic->waitForShutdown();
	 return 0;
  }
};

int 
main(int argc, char* argv[])
{
  Server* app = new Server();
  app->main(argc, argv, "config");
}


