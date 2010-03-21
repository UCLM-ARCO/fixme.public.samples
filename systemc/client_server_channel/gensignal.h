#include "systemc.h"
#include "channel_if.h"

SC_MODULE(gensignal)
{
	sc_in<bool> clock;
	sc_port<channel_write> client_send;

	void genSignals()
	{
		bool s = false;

		while (true)
		{
			client_send->ch_write(s);
			s = !s;
			wait();
		}
	}

	SC_CTOR(gensignal)
	{
		SC_THREAD(genSignals);
		sensitive << clock.pos();
	}
};
