# Subscriber in python.
# Oscar Acena &  Diego Martin

import sys, Ice, IceStorm
import UCLM
import HelloI

class Subscriber(Ice.Application):

    def run(self, argv):
        properties = self.communicator().getProperties();
        proxyProperty = "IceStorm.TopicManager.Proxy";
        proxy = properties.getProperty(proxyProperty);
        if not proxy:
            print self.appName()+": property '"+proxyProperty+"' not set \n"
            return -1

        base = self.communicator().stringToProxy(proxy)
        try:
            manager = IceStorm.TopicManagerPrx.checkedCast(base)
        except Ice.ConnectionRefusedException:
            print self.appName()+": conection to '"+proxy+"' refused\n"
            return -2
        
        if not manager:
            print self.appName()+": invalid proxy\n"
            return -2

        topics = []
        if (len(sys.argv)>1):
            for i in range(1,len(sys.argv)):
                topics.append(sys.argv[i])
        else:
            topics.append("HelloTopic")

        qos = {"reliability":"batch"}

        adapter = self.communicator().createObjectAdapter("Hello.Subscriber");
        helloObj = HelloI.HelloI()

        subscribers = {}

        for p in topics:
            Object = adapter.addWithUUID(helloObj)
            try:
                topic = manager.retrieve(p)
                topic.subscribe(qos, Object)
            except IceStorm.NoSuchTopic, e:
                print self.appName()+": "+e+" name: "+e.ice_name()+"\n"
                break

            subscribers[p] = Object

        if (len(subscribers) == len(topics)):
            adapter.activate()
            self.shutdownOnInterrupt()
            self.communicator().waitForShutdown()

        print "Exiting..."

        for i in subscribers:
            try:
                topic = manager.retrieve(i)
                topic.unsubscribe(subscribers[i])
            except IceStorm.NoSuchTopic, e:
                print self.appName()+": "+e+" name: "+e.ice_name()+"\n"

        return 0

        


# Creamos el suscriptor si se ejecuta como script.
if __name__ == "__main__":
    subs = Subscriber()
    sys.exit(subs.main(sys.argv))


