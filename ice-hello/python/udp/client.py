import sys, traceback, Ice
Ice.loadSlice('hello.ice')
import UCLM

class client (Ice.Application):

    def run(self, argv):

        base = self.communicator().stringToProxy("Hello:udp -p 9999")

        base = base.ice_datagram()
                
        printer = UCLM.HelloPrx.uncheckedCast(base)
        
        if not printer:
            raise RuntimeError("Invalid proxy")
            
        printer.puts("Hello World!")
        
        printer.ice_ping()

        return 0


if __name__ == "__main__":
    client().main(sys.argv)

