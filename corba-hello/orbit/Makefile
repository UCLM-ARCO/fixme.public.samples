CFLAGS=-I/usr/include/glib-1.2 -I/usr/lib/glib/include -I/usr/include/orbit-1.0
LDLIBS=-L/usr/lib -lORBit -lIIOP -lORBitutil -lglib -lm
GENERATED= hello-common.c hello-skels.c hello-stubs.c

all: hello.h server client

server: hello-server.o hello-common.o hello-skels.o
	g++ -o server $^ $(LDLIBS)

client: hello-client.o hello-common.o hello-stubs.o
	g++ -o client $^ $(LDLIBS)


hello.h $(GENERATED): hello.idl
	orbit-idl $<

clean:
	$(RM) $(GENERATED)
	$(RM) *.o client server *~
