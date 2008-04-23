#!/usr/bin/python

import sys, random
import Ice, IceStorm
Ice.loadSlice('hello.ice')
import UCLM


class HelloI(UCLM.Hello):
    def puts(self, s, current=None):
        print "Event received", s


class Subscriber(Ice.Application):
    
    def run(self, argv):

        # Create the object to serve
        endpoint = "default -p %d" % random.randint(10000, 20000)
        adapter = self.communicator().\
                  createObjectAdapterWithEndpoints("Hello.Subscriber",
                                                   endpoint)
        helloObj = HelloI()
        obj_proxy = adapter.addWithUUID(helloObj)

        
        # Get proxy info for Topic Manager
        properties = self.communicator().getProperties();

        prop_key = "IceStorm.TopicManager.Proxy";
        str_proxy = properties.getProperty(prop_key);
        if not str_proxy:
            print "property", prop_key, "not set"
            return 1
        
        print "Using IceStorm in '%s'" % str_proxy
        
        base = self.communicator().stringToProxy(str_proxy)
        topic_mgr = IceStorm.TopicManagerPrx.checkedCast(base)
        if not topic_mgr:
            print 'invalid proxy'
            return 2


        # Get topic and subscribe our object
        try:
            topic = topic_mgr.retrieve("HelloTopic")
            qos = {}
            topic.subscribe(qos, obj_proxy)
        except IceStorm.NoSuchTopic, e:
            print "no such topic found"
            return 3

        print 'Waiting events...'

        adapter.activate()
        self.shutdownOnInterrupt()
        self.communicator().waitForShutdown()

        topic.unsubscribe(obj_proxy)

        return 0


sys.exit(Subscriber().main(sys.argv))


