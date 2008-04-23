CXX=g++-3.4
CC=g++-3.4
CXXFLAGS=`pkg-config --cflags TAO`
LDLIBS=`pkg-config --libs TAO`

all: client server

client: client.o helloC.o
client.o: client.cc helloC.h

server: LDLIBS+=-lTAO_PortableServer
server: server.o helloS.o helloC.o
server.o: server.cc helloS.h helloC.h

%.h %C.h %C.inl %C.cpp %S.h %S.inl %S.cpp: %.idl
	tao_idl -Ge 2 $<

clean:
	$(RM) *~ *.o client server
	$(RM) hello?.* helloS_T.*
