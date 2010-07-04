#!/usr/bin/python -u
# -*- coding: utf-8 -*-

import sys
import time

import Ice
Ice.loadSlice('hello_ami.ice')
import UCLM


class AMI_CallBack(object):
    def ice_response(self, result):
        print "[%s] ice_response: %s" % (time.time(), result)

    def ice_exception(self, ex):
        print "[%s] ice_exception: \n%s" % (time.time(), ex)

        try:
            raise ex
        except Ice.LocalException, e:
            print "EXCEPTION: " + str(e)



class Cliente(Ice.Application):
    def run(self, argv ):
        ic = self.communicator()
        prx = UCLM.HelloAMIPrx.checkedCast(ic.stringToProxy(argv[1]))
        cb = AMI_CallBack()
        print "[%s] before async invocation" % time.time()
        prx.longTimeJob_async(cb)
        print "[%s] after async invocation" % time.time()


s = Cliente()
sys.exit(s.main(sys.argv))
