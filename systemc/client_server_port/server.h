#include "systemc.h"

SC_MODULE(server)
{
	sc_in<bool> request;
	sc_out<bool> send;

	void run()
	{
		send.write( request.read() );
	}

	SC_CTOR(server)
	{
		SC_METHOD(run);
		sensitive << request;
	}
};
