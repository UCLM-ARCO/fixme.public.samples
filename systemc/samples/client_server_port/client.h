#include "systemc.h"

SC_MODULE(client)
{
	sc_in<bool> receive;
	bool state;

	void receive_state()
	{
		state = receive.read();
	}

	SC_CTOR(client)
	{
		SC_METHOD(receive_state);
		sensitive << receive ;
	}
};
