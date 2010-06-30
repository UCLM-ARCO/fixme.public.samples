#include <Ice/Ice.h>
#include <Ice/Application.h>
#include "hello.h"

using namespace std;
using namespace Ice;

class HelloI : public UCLM::Hello {
public:
	void puts(const ::std::string& str,
			  const Current& current) {

		cout << "SERVER: Se recibió el valor " << str << endl;
		cout << "La faceta es " << current.facet << endl;
	}
};

class Server : public Application {
public:
	int run(int argc, char* args[]) {
		shutdownOnInterrupt();

		CommunicatorPtr ic = communicator();

		ObjectAdapterPtr adapter = ic->createObjectAdapter("Server");
		ObjectPtr servant = new HelloI;

		ObjectPrx facet = adapter->addFacet(servant,
											ic->stringToIdentity("Hello"), "hola");
		cout << facet << endl;

		ObjectPrx prx = adapter->add(servant,
									 ic->stringToIdentity("Hello"));
		cout << prx << endl;

		adapter->activate();
		ic->waitForShutdown();
		return 0;
	}
};

int main(int argc, char* argv[]) {
	Server* app = new Server();
	return app->main(argc, argv);
}


