CFLAGS= -ggdb `pkg-config --cflags ORBit-2.0` -I internal
LDLIBS= `pkg-config --libs ORBit-2.0`
GENERATED= hello.h hello-common.c hello-skels.c hello-stubs.c

all: hello.h server client

server: server.o hello-common.o hello-skels.o hello-skelimpl.o

client: client.o hello-common.o hello-stubs.o 

$(GENERATED): hello.idl
	orbit-idl-2 $<

clean:
	$(RM) $(GENERATED)
	$(RM) *.o client server *~


ORBIT_SRC=/home/dvilla/sources/orbit2-2.8.3
internal:
	mkdir internal
	ln -s $(ORBIT_SRC)/linc2/include/linc internal/linc
	ln -s $(ORBIT_SRC)/include/orbit internal/orbit