#!/usr/bin/python
# -*- mode:python; coding:utf-8; tab-width:4 -*-

import sys, Ice, IceStorm
Ice.loadSlice('ASDF.ice')
import ASD

class ASDAI(ASD.ASDA):

    def __init__(self, topic_mgr):
        try:
            self.topic = topic_mgr.create("ASDATopic")
            print "create ASDATopic"
        except IceStorm.TopicExists, e:
            print "topic already created"
            self.topic = topic_mgr.retrieve("ASDATopic")
        
    def addListener(self, listener, current=None):
        qos = {}
        self.topic.subscribe(qos, listener)
        
    def getPublisher(self, current=None):
        pub = self.topic.getPublisher()
        print "-->", pub
        return ASD.ListenerPrx.uncheckedCast(pub)
    
    
class Delegate(Ice.Application):
    def get_topic_manager(self):
        properties = self.communicator().getProperties()

        prop_key = "IceStormAdmin.TopicManager.Default"
        strproxy = properties.getProperty(prop_key)

        if not strproxy:
            print "property", prop_key, "not set"
            return 0

        print "Using IceStorm in '%s'" % strproxy

        base = self.communicator().stringToProxy(strproxy)
        return IceStorm.TopicManagerPrx.checkedCast(base)

    def run(self, argv):
        servant = ASDAI(self.get_topic_manager())

        ic = self.communicator()
        adapter = ic.createObjectAdapterWithEndpoints("Adapter", "tcp -p 3000")

        proxy = adapter.add(servant, ic.stringToIdentity("ASDA"))

        print proxy

        adapter.activate()
        ic.waitForShutdown()
        
        return 0

sys.exit(Delegate().main(sys.argv))



