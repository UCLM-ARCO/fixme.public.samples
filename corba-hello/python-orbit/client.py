#!/usr/bin/env python


import sys, CORBA, std

orb = CORBA.ORB_init()
ior = open("ior").readline()
client = orb.string_to_object(ior)

print client

client.puts("Python Client says Hello")

	
