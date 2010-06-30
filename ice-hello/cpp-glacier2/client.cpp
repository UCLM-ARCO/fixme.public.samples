/*Cliente. Situado en la red externa*/

#include <Ice/Ice.h>
#include <Glacier2/Glacier2.h>
#include <Ice/Application.h>
#include "Printer.h"

using namespace std;

class Client : public Ice::Application
{
public:
  int run(int argc, char* argv[])
  {
    Ice::CommunicatorPtr ic = communicator();
    //Obtenemos el router por defecto.
    Glacier2::RouterPrx router = Glacier2::RouterPrx::checkedCast(ic->getDefaultRouter());
    //Creamos una sesión con el router obtenido.
    //El usuario y pass no se tienen en cuenta.
    Glacier2::SessionPrx session=router->createSession("usuario","pass");

    Ice::ObjectPrx base = ic->stringToProxy(argv[1]);
    Demo::PrinterPrx pr = Demo::PrinterPrx::checkedCast(base);
    if (!pr)
      {
	throw "InvalidProxy";
      }
    pr->printString("Hola Mundo!");
    return 0;
  }
};

int main(int argc, char* argv[])
{
  Client* cli = new Client();
  cli->main(argc, argv);
}
