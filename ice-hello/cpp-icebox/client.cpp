#include <Ice/Ice.h>
#include <Ice/Application.h>
#include "hello.h"

using namespace std;

class Client : public Ice::Application {
public:
  int run (int argv, char* args[]) {
	 Ice::CommunicatorPtr ic = communicator();
	 Ice::ObjectPrx base = ic->stringToProxy(args[1]);
	 UCLM::HelloPrx prx  = UCLM::HelloPrx::checkedCast(base);
	 if (!prx)
		throw "Invalid proxy";

	 cout << "** Enviando Mensaje.  ---> Hello World!" << endl;
	 prx->puts("Hello World!");
	 cout << "** Mensaje Enviado." << endl;

	 return 0;
  }
};


int
main (int argc, char* argv[])
{
  Client* app = new Client();
  app->main(argc, argv);
}
