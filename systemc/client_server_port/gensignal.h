#include "systemc.h"

SC_MODULE(gensignal)
{
	sc_in<bool> clock;
	sc_out<bool> client_send;

	void genSignals()
	{
		bool s = false;
		wait();

		while (true)
		{
			client_send.write(s);
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
