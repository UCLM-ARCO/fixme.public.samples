#include <Ice/Ice.h>
#include <Ice/Application.h>
#include "hello.h"

using namespace Ice;
using namespace UCLM;

struct Client : public Application {
	int run (int argv, char* args[]) {

		CommunicatorPtr ic = communicator();

		ObjectPrx base = ic->stringToProxy(args[1]);
		HelloPrx prx = HelloPrx::checkedCast(base);

		if (!prx) throw "Invalid proxy";

		prx->puts("Hello World!");
		return 0;
	}
};


int main(int argc, char* argv[]) {
	Client* app = new Client();
	return app->main(argc, argv);
}
