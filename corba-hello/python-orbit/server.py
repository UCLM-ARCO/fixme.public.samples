#!/usr/bin/python

import CORBA, std, std__POA

class hello_i(std__POA.hello):
    def puts(self, cad):
        print 'Python server: "%s"' % cad

orb = CORBA.ORB_init()
servant = hello_i()
open("ior", "w").write(orb.object_to_string( servant._this() ))
poa = orb.resolve_initial_references("RootPOA")
poa.the_POAManager.activate()
orb.run()
