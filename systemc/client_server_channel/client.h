#include "systemc.h"
#include "channel_if.h"

SC_MODULE(client)
{
	sc_port<channel_read> receive;
	sc_in<bool> clock;
	bool state;

	void receive_state()
	{
		while (true)
		{
			state = receive->ch_read();
			wait();
		}
	}

	SC_CTOR(client)
	{
		SC_THREAD(receive_state);
		sensitive << clock.pos();
	}
};
