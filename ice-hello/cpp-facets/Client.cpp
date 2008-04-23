#include <Ice/Ice.h>
#include <Ice/Application.h>
#include "hello.h"


class Client : public Ice::Application {
public:
  int run (int argv, char* args[]) {
	 Ice::CommunicatorPtr ic = communicator();
	 Ice::ObjectPrx base = ic->stringToProxy(args[1]);
	 UCLM::HelloPrx object = UCLM::HelloPrx::checkedCast(base,"hola");
	 if (!object)
		throw "Invalid proxy";
	 object->puts("Hello World!");
	 
	 return 0;
  }
};


int
main (int argc, char* argv[])
{
  Client* app = new Client();
  app->main(argc, argv, "config");
}
