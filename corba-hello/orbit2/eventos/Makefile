CFLAGS=-ggdb `pkg-config --cflags ORBit-2.0` #-Wall -O0 "mas información de compilación"
LDLIBS= `pkg-config --libs ORBit-2.0`
IDLDIR=.

generated=$(addprefix $(1), -common.c -stubs.c -skels.c .h)

objs=$(patsubst %.c, %.o, $(filter %.c, $(1)))

all:SimpleEventChannelAdmin.h  CosEventChannel.h CosEventComm.h	hello-supplier hello-consumer channel-factory create-mico-channel

hello-supplier: hello-supplier.o \
	$(call objs, $(call generated, CosEventComm)) \
	$(call objs, $(call generated, CosEventChannel)) \
	SimpleEventChannelAdmin-stubs.o SimpleEventChannelAdmin-common.o 


hello-consumer: hello-consumer.o \
	$(call objs, $(call generated, CosEventComm)) \
	$(call objs, $(call generated, CosEventChannel)) \
	SimpleEventChannelAdmin-stubs.o SimpleEventChannelAdmin-common.o 

channel-factory: channel-factory.c \
	$(call objs, $(call generated, CosEventComm)) \
	$(call objs, $(call generated, CosEventChannel)) 

create-mico-channel: create-mico-channel.o \
	SimpleEventChannelAdmin-stubs.o SimpleEventChannelAdmin-common.o \
	$(call objs, $(call generated, CosEventComm)) \
	$(call objs, $(call generated, CosEventChannel)) 


$(call generated, SimpleEventChannelAdmin): SimpleEventChannelAdmin.idl
	orbit-idl-2 --onlytop -I $(IDLDIR) $< 

$(call generated, CosEventChannel):
	orbit-idl-2 --onlytop -I $(IDLDIR) CosEventChannel.idl

$(call generated, CosEventComm):
	orbit-idl-2 -I $(IDLDIR) CosEventComm.idl



clean:
	$(RM) $(call generated, SimpleEventChannelAdmin)
	$(RM) $(call generated, CosEventComm)
	$(RM) $(call generated, CosEventChannel)
	$(RM) channel-factory create-mico-channel hello-supplier hello-consumer
	$(RM) *.o *~ CosEventChannel.h SimpleEventChannelAdmin.h  CosEventComm.h
