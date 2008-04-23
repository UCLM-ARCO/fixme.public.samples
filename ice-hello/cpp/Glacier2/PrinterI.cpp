#include <PrinterI.h>

using namespace std;

void
Demo::PrinterI::printString(const ::std::string& s,
                            const Ice::Current& current)
{
  cout << s << endl;
}
