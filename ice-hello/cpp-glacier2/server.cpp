/*Servidor. Situado en la red local*/

#include <Ice/Ice.h>
#include <Ice/Application.h>
#include "PrinterI.h"
using namespace std;
using namespace Demo;

class Server : public Ice::Application {
public:
  int run(int argc, char* argv[])
  {
    shutdownOnInterrupt();
    Ice::CommunicatorPtr ic = communicator();
    Ice::ObjectAdapterPtr adapter = ic->createObjectAdapter("Server");
    Ice::ObjectPtr servant = new Demo::PrinterI;
    cout << adapter->add(servant, ic->stringToIdentity("Printer")) << endl;
    adapter->activate();
    ic->waitForShutdown();
    return 0;
  }
};

int main(int argc, char* argv[])
{
  Server* srv = new Server();
  srv->main(argc, argv);
}
