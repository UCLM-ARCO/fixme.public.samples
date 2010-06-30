#!/usr/bin/python -u
# -*- coding: utf-8 -*-

import sys, Ice
Ice.loadSlice('../hello.ice')
import UCLM

class HelloI(UCLM.Hello):
    def puts(self, s, current=None):
        print s


class server(Ice.Application):
    def run(self, argv):
        self.shutdownOnInterrupt()

        # 1) Creamos un adaptador de Objetos.
        adapter = self.communicator(). createObjectAdapter("Server")

        # 2) Instanciamos el objeto HelloI.
        servant = HelloI()

        # 3) Registramos el nuevo sirviente "Hello"
        base = adapter.add(servant, self.communicator().stringToIdentity("Hello"))
        adapter.activate()

        # Referencia del objeto en formato cadena
        print base

        # 4) Activacion del Adaptador.
        self.communicator().waitForShutdown()

        return 0


sys.exit(server().main(sys.argv))
