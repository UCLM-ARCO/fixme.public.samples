
IDL=omniidl
IDLFLAGS= -bcxx
CXXFLAGS= -I. -I/usr/include -I/usr/include/omniORB3 -Wall -Wno-unused
LDFLAGS= -L/usr/lib
LDLIBS= -lomniORB3 -ltcpwrapGK -lomnithread -lpthread
LIBRARIES=/usr/lib/libomniORB3.a /usr/lib/libtcpwrapGK.a /usr/lib/libomnithread.a
CXX=g++-2.95

all: server client

.cc.o .c.o:

%.hh %SK.cc: %.idl
	$(IDL) $(IDLFLAGS) $<

server.cc: hello.idl
	$(IDL) $(IDLFLAGS) -Wbexample $<

server: server.o helloSK.o $(LIBRARIES)

server.o: server.cc hello.hh

%_stubs.cc: %.idl
	$(IDL) $(IDLFLAGS) -Wbs="_stubs.cc" $<

hello_stubs.o: hello_stubs.cc hello.hh

%_stubs.o: %_stubs.cc

client: client.o hello_stubs.o 

client.o: client.cc hello.hh

clean:
	$(RM) *.o client server

vclean: clean
	$(RM) *~ core *SK.cc *.hh *stubs.cc