#!/usr/bin/python

import sys, Ice, IceStorm
Ice.loadSlice('hello.ice')
import UCLM

class Publisher(Ice.Application):

    def run(self, argv):

        # Get proxy info for Topic Manager
        properties = self.communicator().getProperties()

        prop_key = "IceStorm.TopicManager.Proxy"
        endpoint = properties.getProperty(prop_key)
        if not endpoint:
            print "property", prop_key, "not set"
            return 1
        
        print "Using IceStorm in '%s'" % endpoint
            
        base = self.communicator().stringToProxy(endpoint)
        topic_mgr = IceStorm.TopicManagerPrx.checkedCast(base)
        if not topic_mgr:
            print 'invalid proxy'
            return 2

        
        # Get topic
        try:
            topic = topic_mgr.retrieve("HelloTopic")
        except IceStorm.NoSuchTopic, e:
            print "no such topic found, created"
            topic = topic_mgr.create("HelloTopic")


        # Get publisher and call remote object method
        prx = topic.getPublisher()
            
        hello = UCLM.HelloPrx.uncheckedCast(prx)

        print "publishing 10 'Hello World' events"
        for i in range(10):
            hello.puts("Hello world!")

        return 0       


sys.exit(Publisher().main(sys.argv))

