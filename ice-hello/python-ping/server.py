#!/usr/bin/python -u
# -*- coding: utf-8 -*-

import sys, Ice
Ice.loadSlice('../hello.ice')
import UCLM

class HelloI(UCLM.Hello):
    def puts(self, s, current=None):
        print s

    def ice_ping(self, current=None):
        print "ping"


class server(Ice.Application):
    def run(self, argv):
        self.shutdownOnInterrupt()

        adapter = self.communicator().createObjectAdapter("Server")
        servant = HelloI()
        base = adapter.add(servant, self.communicator().stringToIdentity("Hello"))
        adapter.activate()

        print base

        self.communicator().waitForShutdown()

        return 0


if __name__ == "__main__":
    sys.exit(server().main(sys.argv))
