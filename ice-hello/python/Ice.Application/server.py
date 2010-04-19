import sys, Ice
Ice.loadSlice('hello.ice')
import UCLM


class HelloI(UCLM.Hello):
    def puts(self, s, current=None):
        print "Client say: ", s


class Server(Ice.Application):
    def run(self, argv):

        self.shutdownOnInterrupt()

        # 1) Creamos un adaptador de Objetos.
        adapter = self.communicator().createObjectAdapter("Servidor")

        # 2) Instanciamos el objeto HelloI.
        obj = HelloI()

        # 3) Informamos al adaptador acerca de un nuevo sirviente "Hello"
        prx = adapter.add(obj, self.communicator().stringToIdentity("Hello"))

        # 4) Activacion del Adaptador.
        adapter.activate()

        print self.communicator().proxyToString(prx)

        self.communicator().waitForShutdown()


Server().main(sys.argv, 'config')
