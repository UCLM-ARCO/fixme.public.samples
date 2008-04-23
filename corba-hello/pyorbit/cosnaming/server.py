#!/usr/bin/python

import sys, ORBit

ORBit.load_typelib('./hello_module.so')
ORBit.load_typelib('./CosNaming_module.so')


import CORBA, HelloModule, HelloModule__POA
import CosNaming

class hello_i(HelloModule__POA.hello):
    def puts(self, cad):
        print 'Python server: "%s"' % cad


orb = CORBA.ORB_init()

servant = hello_i()

nc = orb.string_to_object(sys.argv[1])._narrow(CosNaming.NamingContext)

name = [CosNaming.NameComponent('hello', '')]
nc.bind(name, servant._this())

poa = orb.resolve_initial_references("RootPOA")
poa.the_POAManager.activate()
orb.run()
