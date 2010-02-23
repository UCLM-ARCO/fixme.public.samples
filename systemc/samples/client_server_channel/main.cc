#include "systemc.h"

#include "server.h"
#include "client.h"
#include "gensignal.h"
#include "mon.h"
#include "channel.h"

int sc_main(int arc, char* argv [])
{
  sc_clock clock("Clock", 0.1, SC_SEC); //flanco de reloj cada 0.1 segundos
  Channel canalR("ChannelR");
  Channel canalW("ChannelW");

  server theServer("Server");
  theServer.request(canalR);
  theServer.send(canalW);
  theServer.clock(clock);

  client theClient0("Client0");
  theClient0.receive(canalW);
  theClient0.clock(clock);

  client theClient1("Client1");
  theClient1.receive(canalW);
  theClient1.clock(clock);

  gensignal theSignals("Generator");
  theSignals.client_send(canalR);
  theSignals.clock(clock);

  mon monitor("Monitor");
  monitor.s_send(canalW);
  monitor.s_request(canalR);
  monitor.clock(clock);

  sc_start(sc_time(2.0,SC_SEC)); //2 segundos de simulacion
}
