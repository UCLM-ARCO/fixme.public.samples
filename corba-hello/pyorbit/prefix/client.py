#!/usr/bin/env python

import sys, ORBit

ORBit.load_typelib('./hello_module.so')

#ORBit.load_file('./hello.idl')

print sys.modules

import CORBA, uclm.es


orb = CORBA.ORB_init()
client = orb.string_to_object(sys.argv[1])

client = client._narrow(uclm.HelloModule.hello)

client.puts("Python Client says Hello")

	
