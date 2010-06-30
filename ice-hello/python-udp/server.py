#!/usr/bin/python -u
# -*- coding: utf-8 -*-

import sys, Ice
Ice.loadSlice('../hello.ice')
import UCLM


class HelloI(UCLM.Hello):
    def puts(self, s, current=None):
        print s


class Server(Ice.Application):
    def run(self, argv):
        self.shutdownOnInterrupt()

        ic = self.communicator()

        servant = HelloI()

        adapter = ic.createObjectAdapter(argv[1])
        base = adapter.add(servant, ic.stringToIdentity("Hello"))
        adapter.activate()

        print base

        ic.waitForShutdown()

        return 0


sys.exit(Server().main(sys.argv))
