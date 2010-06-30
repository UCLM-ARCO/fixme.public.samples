#!/usr/bin/python -u
# -*- coding: utf-8 -*-

import sys, time
import Ice
Ice.loadSlice('hello_ami.ice')
import UCLM

class HelloAMII(UCLM.HelloAMI):
    def longTimeJob(self, ctx=None):
        print "[%s] method execution begins" % time.time()
        time.sleep(3)
        print "[%s] method execution ends" % time.time()
        return "longTimeJob retval"


class Server(Ice.Application):
    def run(self, argv):
        ic = self.communicator()
        self.shutdownOnInterrupt()

        adapter = ic.createObjectAdapter("Server")

        servant = HelloAMII()
        base = adapter.add(servant, ic.stringToIdentity("Hello"))
        adapter.activate()

        print base
        print '[%s] server starts' % time.time()

        ic.waitForShutdown()

        return 0

if __name__ == "__main__":
    s = Server()
    sys.exit(s.main(sys.argv))
