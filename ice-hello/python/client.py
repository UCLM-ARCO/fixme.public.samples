#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys, Ice
Ice.loadSlice('../hello.ice')
import UCLM

class client (Ice.Application):

    def run(self, argv):
        base = self.communicator().stringToProxy(argv[1])

        printer = UCLM.HelloPrx.checkedCast(base)

        if not printer:
            raise RuntimeError("Invalid proxy")

        printer.puts("Hello World!")

        return 0


sys.exit(client().main(sys.argv))
