CFLAGS= `pkg-config --cflags ORBit-2.0`
LDLIBS= `pkg-config --libs ORBit-2.0`
GENERATED= hello.h hello-common.c hello-skels.c hello-stubs.c

all: hello.h hello-server hello-client

hello-server: hello-server.o hello-common.o hello-skels.o hello-skelimpl.o
hello-client: hello-client.o hello-common.o hello-stubs.o 

$(GENERATED): hello.idl
	orbit-idl-2 $<

clean:
	$(RM) $(GENERATED)
	$(RM) *.o hello-client hello-server *~
