#ifndef __PrinterI_h__
#define __PrinterI_h__

#include <Printer.h>

namespace Demo
{

class PrinterI : virtual public Printer
{
public:

    virtual void printString(const ::std::string&,
                             const Ice::Current&);
};

}

#endif
