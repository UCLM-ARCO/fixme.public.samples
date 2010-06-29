#include <Ice/Ice.h>
#include <Ice/Application.h>
#include "hello.h"

using namespace std;
using namespace Ice;
using namespace UCLM;

struct HelloI: public Hello {
	void puts(const string& str, const Current& current) {
		cout << str << endl;
	}
};

struct Server : public Application {
  int run(int argc, char* args[]) {
	 shutdownOnInterrupt();

	 CommunicatorPtr ic = communicator();
	 ObjectAdapterPtr adapter = ic->createObjectAdapter("Server");

	 ObjectPtr servant = new HelloI;
	 ObjectPrx base = adapter->add(servant, ic->stringToIdentity("Hello"));
	 adapter->activate();

	 cout << ic->proxyToString(base) << endl;

	 ic->waitForShutdown();
	 return 0;
  }
};

int main(int argc, char* argv[]) {
  Server* app = new Server();
  return app->main(argc, argv, argv[1]);
}


