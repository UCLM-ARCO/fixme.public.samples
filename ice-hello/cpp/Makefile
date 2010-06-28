
LDLIBS=-lIce

SLICE=hello
all: server client

server.cc client.cc: $(SLICE).h

%.h %.cc: ../%.ice
	slice2cpp $<

server: server.o $(SLICE).o
client: client.o $(SLICE).o

clean:
	$(RM) server client *.o *~

vclean: clean
	$(RM) *~ $(SLICE).cpp $(SLICE).h
