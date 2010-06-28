# Publisher in python.
# Oscar Acena & Diego Martin

import sys, Ice, IceStorm
import UCLM

class Publisher(Ice.Application):

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

        try:
            topic = manager.retrieve("HelloTopic")
        except Ice.Storm.NoSuchTopic, e:
            print self.appName()+": "+e+" name: "+e.name+"\n"
            return -3

        assert topic

        obj = topic.getPublisher()
        if not obj.ice_isDatagram():
            obj = obj.ice_oneway()
            
        hello = UCLM.HelloPrx.uncheckedCast(obj)

        print "publishing 10 'Hello World' events\n"
        for i in range(10):
            hello.puts("Hello world!")

        return 0       


# Creamos el publicador si se ejecuta como script.
if __name__ == "__main__":
    pub = Publisher()
    sys.exit(pub.main(sys.argv))
