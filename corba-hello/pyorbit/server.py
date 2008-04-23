#!/usr/bin/python

import os, ORBit
import threading

ORBit.load_typelib('./hello_module.so')
# Alternativamente se puede usar 
# ORBit.load_file('hello.idl')

import CORBA, HelloModule, HelloModule__POA

class hello_i(HelloModule__POA.hello):
    def puts(self, cad):
        print 'Python server: "%s"' % cad

orb = CORBA.ORB_init()
servant = hello_i()

print orb.object_to_string( servant._this() )

poa = orb.resolve_initial_references("RootPOA")
poa.the_POAManager.activate()


def orb_thread():
    if orb.work_pending(): orb.perform_work()
    threading.Timer(0.1, orb_thread).start()

orb_thread()    
