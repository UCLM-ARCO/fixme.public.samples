#!/usr/bin/python -u
# -*- mode:python; coding:utf-8; tab-width:4 -*-

import sys, Ice, IceStorm
Ice.loadSlice('ASDF.ice')
import ASD

class ListenerI(ASD.Listener):
    def adv(self, s, current=None):
        print "Hola"

class Subscriber(Ice.Application):

    def run(self, argv):
        servant = ListenerI()

        ic = self.communicator()
        adapter = ic.createObjectAdapter("Listener.Subscriber")

        proxy = adapter.addWithUUID(servant)

        base = self.communicator().stringToProxy(argv[1])
        delegate = ASD.ASDAPrx.checkedCast(base)
        print "::", delegate

        listener = ASD.ListenerPrx.uncheckedCast(proxy)
        delegate.addListener(listener)
        
        print 'SUBSCRIBED!!'
        print "Waiting events..."

        adapter.activate()
        ic.waitForShutdown()
        
        return 0


sys.exit(Subscriber().main(sys.argv))
