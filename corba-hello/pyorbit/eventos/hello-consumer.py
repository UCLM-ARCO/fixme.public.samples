#!/usr/bin/python2.3

import os, ORBit, CORBA,  sys

#ORBit.load_typelib('./CosEventChannel_module.so')
ORBit.load_file('./CosEventChannel.idl')
ORBit.load_file('./CosEventComm.idl')

import CosEventChannelAdmin
import CosEventComm, CosEventComm__POA


# Definimos nuestro push_consumer.
class push_consumer_impl(CosEventComm__POA.PushConsumer):
    def push(self, data):
        print "* Consumer: Evento Recibido"
        print "* Consumer:", data.value()
    def disconnect_push_consumer(self):
        pass #...



# Iniciamos el ORB.
orb = CORBA.ORB_init()

poa = orb.resolve_initial_references("RootPOA")
poa.the_POAManager.activate()


# Creamos nuestro push_consumer
p_consumer =  push_consumer_impl()

# Instanciamos el Canal de eventos.
channel = orb.string_to_object(sys.argv[1])
channel = channel._narrow(CosEventChannelAdmin.EventChannel)

# Obtenemos el ConsumerAdmin.
consumer_admin = channel.for_consumers()#._narrow(CosEventChannelAdmin.ConsumerAdmin)

# Obtenemos el ProxyPushSupplier.
proxy_supplier = consumer_admin.obtain_push_supplier()#._narrow(CosEventChannelAdmin.ProxyPushSupplier)

# Conectamos el push_consumer al ProxyPushConsumer.
proxy_supplier.connect_push_consumer(p_consumer._this())

orb.run()
