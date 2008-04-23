#!/usr/bin/python

import os, ORBit

ORBit.load_typelib('./bye_module.so')

import CORBA, ByeModule, ByeModule__POA

class bye_i(ByeModule__POA.bye):
    def gets(self):
        retval = CORBA.Any(CORBA.TC_string, "Python server says bye!")
        return retval

orb = CORBA.ORB_init()
servant = bye_i()

print orb.object_to_string( servant._this() )

poa = orb.resolve_initial_references("RootPOA")
poa.the_POAManager.activate()



orb.run()
