#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys, Ice
Ice.loadSlice('hello.ice')
import UCLM

class HelloI(UCLM.Hello):
    def puts(self, s, current=None):
        print "Client say: ", s


class server(Ice.Application):
    def run(self, argv):
        self.shutdownOnInterrupt()

        # 1) Creamos un adaptador de Objetos.
        adapter = self.communicator().\
                  createObjectAdapterWithEndpoints("Server", "default -p 9999")

        # 2) Instanciamos el objeto HelloI.
        servant = HelloI()

        # 3) Registramos el nuevo sirviente "Hello"
        obj = adapter.add(servant, self.communicator().stringToIdentity("Hello"))

        # Referencia del objeto en formato cadena
        print obj

        # 4) Activacion del Adaptador.
        adapter.activate()
        self.communicator().waitForShutdown()

        return 0


sys.exit(server().main(sys.argv))
