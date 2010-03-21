#include "systemc.h"

#include "server.h"
#include "client.h"
#include "gensignal.h"
#include "mon.h"


int sc_main(int arc, char* argv [])
{
  sc_clock clock("Clock", 10.0, SC_NS);
  sc_signal<bool> s_request, s_send;

  server theServer("Server");
  theServer.request(s_request);
  theServer.send(s_send);

  client theClient("Client");
  theClient.receive(s_request);

  gensignal theSignals("Generator");
  theSignals.clock(clock);
  theSignals.client_send(s_request);

  mon monitor("Monitor");
  monitor.s_send(s_send);
  monitor.s_request(s_request);
  monitor.clock(clock);

  sc_start(50);
}
