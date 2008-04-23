#!/usr/bin/python

import os, ORBit

ORBit.load_typelib('./hello_module.so')

import CORBA, HelloModule, HelloModule__POA

class hello_i(HelloModule__POA.hello):
    def puts(self, any):
        print 'Python server:', any.value(), "(type:", any.typecode().name, ")"
        if any.typecode() == CORBA.TC_string:
            print "es una cadena"

orb = CORBA.ORB_init()
servant = hello_i()

print orb.object_to_string( servant._this() )

poa = orb.resolve_initial_references("RootPOA")
poa.the_POAManager.activate()
orb.run()
