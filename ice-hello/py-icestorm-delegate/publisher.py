#!/usr/bin/python
# -*- mode:python; coding:utf-8; tab-width:4 -*-

import Ice, IceStorm
Ice.loadSlice('ASDF.ice')
import ASD, sys

class Publisher(Ice.Application):
    def run(self, argv):
        base = self.communicator().stringToProxy(argv[1])
        delegate = ASD.ASDAPrx.checkedCast(base)
        print base
        
        publisher = delegate.getPublisher()
        
        prx = ASD.ListenerPrx.uncheckedCast(publisher)
        
        print "Publishing..."
        for i in range(5):
            prx.adv("Hello!!")

        return 0

sys.exit(Publisher().main(sys.argv))
