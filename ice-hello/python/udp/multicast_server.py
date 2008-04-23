import sys, traceback, Ice
Ice.loadSlice('hello.ice')
import UCLM
import socket, struct

mcast_group = '225.100.100.100'
port = 9999


class HelloI(UCLM.Hello):
    def puts(self, s, current=None):
        print "Client say: ", s


class server(Ice.Application):

    def mcast_memership(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.bind(('', port))
        mreq = struct.pack('4sl',
                           socket.inet_aton(mcast_group),
                           socket.INADDR_ANY)

        self.sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)
        
            
    def run(self, argv):
        self.shutdownOnInterrupt()

        self.mcast_memership()
        endpoint = "udp -h %s -p %s" % (mcast_group, port)
        adapter = self.communicator().\
                  createObjectAdapterWithEndpoints("Server", endpoint)

        obj = HelloI()

        adapter.add(obj, Ice.stringToIdentity("Hello"))
    
        adapter.activate()
        self.communicator().waitForShutdown()
            
        return 0
    

if __name__ == "__main__":
    server().main(sys.argv)
