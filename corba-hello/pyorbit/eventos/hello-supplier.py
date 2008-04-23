#!/usr/bin/python

import os, ORBit, sys, time
ORBit.load_file('./CosEventChannel.idl')
#ORBit.load_typelib('./CosEventChannel_module.so')

import CORBA
#import CosEventChannel

orb = CORBA.ORB_init()

# Instanciamos el Canal de eventos.
channel = orb.string_to_object(sys.argv[1])#._narrow(CosEventChannelAdmin.EventChannel)

# Obtenemos el SupplierAdmin.
supplier_admin = channel.for_suppliers()#._narrow(CosEventChannelAdmin.SupplierAdmin)

# Obtenemos el ProxyPushConsumer.
proxy_consumer = supplier_admin.obtain_push_consumer()#._narrow(CosEventChannelAdmin.ProxyPushConsumer)

# Conectamos el push_consumer al ProxyPushConsumer.
proxy_consumer.connect_push_supplier(None)

# Enviamos el evento.
print "* Supplier: Enviando Evento."
print
time.sleep(2) # Retardo intencionado 
event = CORBA.Any(CORBA.TC_string,"Hola mundo\n")
proxy_consumer.push(event)



