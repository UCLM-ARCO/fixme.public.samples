#include "systemc.h"
#include "channel_if.h"

class Channel: public sc_module,
			   public channel_read,
			   public channel_write
{

private:
  bool msg;

public:

  Channel(sc_module_name nm) : sc_module(nm), msg(0)
  {
  }

  void ch_write(bool b)
  {
	msg = b;
  }

  bool ch_read()
  {
	return msg;
  }

  void register_port(sc_port_base& port_,
					 const char* if_typename_)
  {
    cout << "Binding    " << port_.name() << " to "
         << "interface: " << if_typename_ << endl;
  }

};
