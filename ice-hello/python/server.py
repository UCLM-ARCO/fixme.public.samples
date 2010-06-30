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

        # 1) Create object adapter
        adapter = ic.createObjectAdapter("Server")

        # 2) Create servant (HelloI instance)
        servant = HelloI()

        # 3) Register servant in the adaptor
        base = adapter.add(servant, ic.stringToIdentity("Hello"))
        adapter.activate()

        # Print remote object reference
        print base

        # 4) wait server ends
        ic.waitForShutdown()

        return 0


sys.exit(Server().main(sys.argv))
