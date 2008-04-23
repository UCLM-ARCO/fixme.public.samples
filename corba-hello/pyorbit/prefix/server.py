#!/usr/bin/python

import os, ORBit

ORBit.load_typelib('./hello_module.so')

import imp, sys

#print imp.find_module("org")

#print dir(sys)
#print sys.modules

import CORBA


class hello_i(uclm.es__POA.HelloModule.hello):
    def puts(self, cad):
        print 'Python server: "%s"' % cad

orb = CORBA.ORB_init()
servant = hello_i()

print orb.object_to_string( servant._this() )

poa = orb.resolve_initial_references("RootPOA")
poa.the_POAManager.activate()
orb.run()
