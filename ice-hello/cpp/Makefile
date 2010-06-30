
CC=g++
CXXFLAGS=-I.
LDLIBS=-lIce

SLICE=hello
STUBS=$(addprefix $(SLICE), .h .cpp)

all: server client

server: server.o $(SLICE).o
client: client.o $(SLICE).o

server.cpp client.cpp: $(STUBS)

vpath %.ice ../

%.h %.cpp: %.ice
	slice2cpp $<

clean:
	$(RM) server client *.o *~ proxy.out
	$(RM) $(STUBS)

run-server: server
	./server --Ice.Config=../config | tee proxy.out

run-client: client
	./client "$(shell head -1 proxy.out)"
