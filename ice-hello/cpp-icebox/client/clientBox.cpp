#include <Ice/Ice.h>
#include <Ice/Application.h>
#include "hello.h"

using namespace std;

class Client : public Ice::Application {
public:
  int run (int argv, char* args[]) {
	 Ice::CommunicatorPtr ic = communicator();
	 
	 Ice::PropertiesPtr properties = ic->getProperties();
	 const char* proxyProperty = "HelloService.Proxy";
	 std::string proxy = properties->getProperty(proxyProperty);
	 if(proxy.empty())
	   {
	     return EXIT_FAILURE;
	   }

	 
	 Ice::ObjectPrx base = ic->stringToProxy(proxy); 
	 UCLM::HelloPrx object = UCLM::HelloPrx::checkedCast(base);
	 if (!object)
		throw "Invalid proxy";

	 cout << "** Enviando Mensaje.  ---> Hello World!" << endl;
	 object->puts("Hello World!");
	 cout << "** Mensaje Enviado." << endl;
	 
	 return 0;
  }
};


int
main (int argc, char* argv[])
{
  Client* app = new Client();
  app->main(argc, argv, "config_box");
}
