#!/usr/bin/env python

import sys, ORBit

ORBit.load_typelib('./hello_module.so')
ORBit.load_typelib('./CosNaming_module.so')


import CORBA, HelloModule, CosNaming

orb = CORBA.ORB_init()

nc = orb.string_to_object(sys.argv[1])._narrow(CosNaming.NamingContext)

name = [CosNaming.NameComponent('hello', '')]
client = nc.resolve(name)._narrow(HelloModule.hello)

client.puts("Python Client says Hello")

	
