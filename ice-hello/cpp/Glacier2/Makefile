CFLAGS+=-I. -I/usr/include
LDLIBS+=-I. -I/usr/include -I/usr/include/Ice -L/usr/lib -lIce -lIceUtil -I/usr/include/Glacier2 -lGlacier2

CXXFLAGS+=$(CFLAGS)


CC=gcc
CXX=g++



GENERATED = Printer

all: config $(GENERATED).cpp Server Client

Server: Server.o $(GENERATED).o $(GENERATED)I.o

Server.o: Server.cpp

Client: Client.cpp $(GENERATED).o

$(GENERATED): $(GENERATED).cpp

$(GENERATED).o: $(GENERATED).cpp

$(GENERATED).cpp: $(GENERATED).ice
	slice2cpp $<

clean:
	$(RM) *.o
	$(RM) Server Client

vclean: clean
	$(RM) *~ $(GENERATED).cpp $(GENERATED).h
	$(RM) config *.ice