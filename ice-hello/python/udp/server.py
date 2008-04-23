import sys, traceback, Ice
Ice.loadSlice('hello.ice')
import UCLM

class HelloI(UCLM.Hello):
    def puts(self, s, current=None):
        print "Client say: ", s


class server(Ice.Application):
            
    def run(self, argv):
        self.shutdownOnInterrupt()

        adapter = self.communicator().\
                  createObjectAdapterWithEndpoints("Server", "udp -p 9999")

        obj = HelloI()

        adapter.add(obj, Ice.stringToIdentity("Hello"))
    
        adapter.activate()
        self.communicator().waitForShutdown()
            
        return 0
    

if __name__ == "__main__":
    server().main(sys.argv)
