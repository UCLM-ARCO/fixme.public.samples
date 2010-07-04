#!/usr/bin/python -u
# -*- coding: utf-8 -*-

import sys, Ice
Ice.loadSlice('../hello.ice')
import UCLM

class client (Ice.Application):

    def run(self, argv):
        base = self.communicator().stringToProxy(argv[1])
        prx = UCLM.HelloPrx.checkedCast(base)

        if not prx:
            raise RuntimeError("Invalid proxy")

        prx.puts("Hello World!")
        prx.ice_ping()

        return 0


if __name__ == "__main__":
    sys.exit(client().main(sys.argv))
