import sys, traceback, Ice
Ice.loadSlice('hello.ice')
import UCLM

class HelloI(UCLM.Hello):
    def puts(self, s, current=None):
        print "Client say: ", s

    def ice_ping(self, current=None):
        print "ping"

class server(Ice.Application):
    def run(self, argv):
        self.shutdownOnInterrupt()
    
        # 1) Creamos un adaptador de Objetos.
        adapter = self.communicator().\
                  createObjectAdapterWithEndpoints("Server", "default -p 9999")

        # 2) Instanciamos el objeto HelloI.
        obj = HelloI()

        # 3) Informamos al adaptador acerca del nuevo sirviente "Hello"
        adapter.add(obj, Ice.stringToIdentity("Hello"))

        # 4) Activacion del Adaptador.
        adapter.activate()
        self.communicator().waitForShutdown()
            
        return 0


if __name__ == "__main__":
    sys.exit(server().main(sys.argv))
