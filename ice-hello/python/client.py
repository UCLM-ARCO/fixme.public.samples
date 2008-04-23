import sys, traceback, Ice
Ice.loadSlice('hello.ice')
import UCLM

class client (Ice.Application):
        
    def run(self, argv):
        base = self.communicator().stringToProxy("Hello:default -p 9999")
    
        printer = UCLM.HelloPrx.checkedCast(base)
            
        if not printer:
            raise RuntimeError("Invalid proxy")
            
        printer.puts("Hello World!")

        return 0


if __name__ == "__main__":
    sys.exit(client().main(sys.argv))
