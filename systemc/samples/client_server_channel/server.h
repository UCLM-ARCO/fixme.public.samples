#include "systemc.h"
#include "channel_if.h"

SC_MODULE(server)
{
	sc_port<channel_read> request;
	sc_port<channel_write> send;
    sc_in<bool> clock;


	void run()
	{
		bool received;

		while (true)
		{
			received = request->ch_read();
			send->ch_write(received);
			wait();
		}
	}

	SC_CTOR(server)
	{
		SC_THREAD(run);
		sensitive << clock.pos();
	}
};
