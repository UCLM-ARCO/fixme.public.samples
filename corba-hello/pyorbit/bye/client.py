#!/usr/bin/env python

import sys, ORBit

ORBit.load_typelib('./bye_module.so')

import CORBA
from ByeModule import bye

orb = CORBA.ORB_init()
client = orb.string_to_object(sys.argv[1])

print "Python client: ", client.gets()

	
