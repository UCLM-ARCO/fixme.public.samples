import Ice
import sys
import time
Ice.loadSlice('hello_ami.ice')
import UCLM


class AMI_CallBack(object):
    def ice_response(self, result):
        print "[%s] ice_response: \n%s" % (time.time(), result)

    def ice_exception(self, ex):
        print "[%s] ice_exception: \n%s" % (time.time(), ex)

        try:
            raise ex
        except Ice.LocalException, e:
            print "EXCEPTION: " + str(e)



class Cliente(Ice.Application):
    def run(self, argv ):
        c = self.communicator()
        minimo = UCLM.HelloAMIPrx.checkedCast(c.stringToProxy(argv[1]))
        cb = AMI_CallBack()
        print "[%s] antes de llamar" % time.time()
        minimo.longTimeJob_async(cb)
        print "[%s] despues de llamar" % time.time()
        print "puedo seguir haciendo cosas"


s = Cliente()
sys.exit(s.main(sys.argv))
