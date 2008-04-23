#!/usr/bin/env python

import sys, ORBit

ORBit.load_typelib('./hello_module.so')

import CORBA
from HelloModule import hello

orb = CORBA.ORB_init()
client = orb.string_to_object(sys.argv[1])._narrow(hello)

client.puts(CORBA.Any(CORBA.TC_string, "PyORBit Client says Hello"))

	
