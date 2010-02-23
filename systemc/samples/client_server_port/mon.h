#include "systemc.h"
#include <iostream>

SC_MODULE(mon)
{
	sc_in<bool> s_request, s_send; //server_request, server_send
    sc_in<bool> clock;

	void monitor()
	{
		cout << "\nTime";
		cout << "\ts_request" ;
		cout << "\ts_send" << endl;
		while (true)
		{
			std::cout << sc_time_stamp();
			std::cout << "\t" << s_request.read();
			std::cout << "\t\t" << s_send.read() << std::endl;
			wait();
		}
	}

	SC_CTOR(mon)
	{
		SC_THREAD(monitor);
		sensitive << clock.pos();
	}
};
