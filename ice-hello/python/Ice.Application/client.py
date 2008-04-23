import sys, Ice
Ice.loadSlice('hello.ice')
import UCLM

class Client (Ice.Application):
    def run(self, argv):
        obj = self.communicator().stringToProxy(argv[1])

        hello = UCLM.HelloPrx.checkedCast(obj)
        if not hello:
            raise RuntimeError("Invalid proxy")
            
        hello.puts("Hello World!")
        return 0


Client().main(sys.argv, 'config')
