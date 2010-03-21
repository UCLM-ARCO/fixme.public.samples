#include "systemc.h"
#include "channel_if.h"
#include <iostream>

SC_MODULE(mon)
{
	sc_port<channel_read> s_request, s_send;
    sc_in<bool> clock;

	void monitor()
	{
		cout << "\nTime";
		cout << "\tChannelR" ;
		cout << "\tChannelW" << endl;
		while (true)
		{
			std::cout << sc_time_stamp();
			std::cout << "\t" << s_request->ch_read();
			std::cout << "\t\t" << s_send->ch_read() << std::endl;
			wait();
		}
	}

	SC_CTOR(mon)
	{
		SC_THREAD(monitor);
		sensitive << clock.pos();
	}
};
