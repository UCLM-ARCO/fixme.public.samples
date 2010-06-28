#include <Ice/Ice.h>
#include <Ice/Application.h>
#include "hello.h"

using namespace Ice;
using namespace UCLM;

struct Client : public Application {
	int run (int argv, char* args[]) {
		CommunicatorPtr ic = communicator();
		ObjectPrx base = ic->stringToProxy(args[1]);
		UCLM::HelloPrx object = UCLM::HelloPrx::checkedCast(base);
		if (!object)
			throw "Invalid proxy";
		object->puts("Hello World!");

		return 0;
	}
};


int main (int argc, char* argv[]) {
	Client* app = new Client();
	app->main(argc, argv, "config");
}
