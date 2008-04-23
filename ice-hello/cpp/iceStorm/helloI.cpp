#include <Ice/Ice.h>
#include <helloI.h>

/*
 * Este fichero fue generado en primera instancia mediante:
 *
 * $ slice2cpp --impl hello.ice
 *
 * y posteriormente modificado
 */

using namespace std;

void
UCLM::HelloI::puts(const ::std::string& s,
		   const Ice::Current& current)
{
  cout << "Event received: " << s << endl;
}

