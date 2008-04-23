#!/usr/bin/env python

import sys, ORBit

ORBit.load_typelib('./hello_module.so')

import CORBA
import HelloModule

orb = CORBA.ORB_init()
client = orb.string_to_object(sys.argv[1])._narrow(HelloModule.hello)

client.puts("PyORBit Client says Hello")

	
