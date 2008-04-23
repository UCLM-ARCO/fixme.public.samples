#!/usr/bin/python

import os, ORBit, sys

ORBit.load_typelib('./CosEventChannel_module.so')

import CORBA
import CosEventChannelAdmin

orb = CORBA.ORB_init()

channel = orb.string_to_object(sys.argv[1])._narrow(EventChannel)

supplier_admin = channel.for_suppliers()._narrow(SupplierAdmin)

proxy_consumer = supplier_admin.obtain_push_consumer()._narrow(ProxyPushConsumer)

proxy_consumer.connect_push_supplier(nil)

event = CORBA.any(TC_CORBA_string,"Hola mundo\n")

proxy_consumer.push(event)



