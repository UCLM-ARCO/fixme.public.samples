CFLAGS+=-I. -I/usr/include
LDLIBS+=-I. -I/usr/include -I/usr/include/Ice -L/usr/lib -lIce -lIceUtil -I/usr/include/Glacier2 -lGlacier2

CXXFLAGS+=$(CFLAGS)


CC=gcc
CXX=g++



GENERATED = Printer

all: $(GENERATED).cpp server client

server: server.o $(GENERATED).o $(GENERATED)I.o

server.o: server.cpp

client: client.cpp $(GENERATED).o

$(GENERATED): $(GENERATED).cpp

$(GENERATED).o: $(GENERATED).cpp

$(GENERATED).cpp: $(GENERATED).ice
	slice2cpp $<

clean:
	$(RM) *.o
	$(RM) server client
	$(RM) *~ $(GENERATED).cpp $(GENERATED).h

run-glacier2:
	glacier2router --Ice.Config=glacier.conf

run-server:
	./server --Ice.Config=config | tee proxy.out

run-client:
	./client --Ice.Config=config "$(shell head -1 proxy.out)"
