import Ice
import sys
import time
Ice.loadSlice('hello_ami.ice')
import UCLM

class HelloAMII(UCLM.HelloAMI):
    def longTimeJob(self, ctx=None):
        print "[%s] Entro en la llamada que dura mucho" % time.time()
        time.sleep(10)
        print "[%s] Termina la llamada" % time.time()
        return "longTimeJob retval"


class Server(Ice.Application):
    def run(self, argv):
        m = HelloAMII()
        c = self.communicator()
        oa = c.createObjectAdapterWithEndpoints("adapter", "tcp")
        print "[%s] %s" % (time.time(), oa.add(m, c.stringToIdentity("hello-ami")))
        oa.activate()

        c.waitForShutdown()


if __name__ == "__main__":
    s = Server()
    sys.exit(s.main(sys.argv))
