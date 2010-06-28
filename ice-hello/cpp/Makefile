
CC=g++
CXXFLAGS=-I.
LDLIBS=-lIce

SLICE=hello

all: server client

server.cpp client.cpp: $(SLICE).h $(SLICE).cpp

vpath %.ice ../

%.h %.cpp: %.ice
	slice2cpp $<

server: server.o $(SLICE).o
client: client.o $(SLICE).o

config: ../config
	ln -s $< $@

clean:
	$(RM) server client *.o *~
	$(RM) $(SLICE).* proxy.out

run-server: server config
	./server --Ice.Config=config | tee proxy.out

run-client: client
	./client "$(shell head -1 proxy.out)"
