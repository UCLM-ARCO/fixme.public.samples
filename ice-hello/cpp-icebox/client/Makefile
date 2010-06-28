CFLAGS+=-I. -I/usr/include -I/usr/local/include
CFLAGS+=-I./

LDLIBS+=-I. -I/usr/include -I/usr/include/Ice -L/usr/lib -lIce -lIceUtil \
	 -L/usr/local/lib -L.

CXXFLAGS+=$(CFLAGS)

CC=gcc
CXX=g++

GENERATED = hello

all: $(GENERATED).cpp clientBox

clientBox: clientBox.cpp $(GENERATED).o

$(GENERATED): $(GENERATED).cpp

$(GENERATED).o: $(GENERATED).cpp

$(GENERATED).cpp: $(GENERATED).ice
	slice2cpp $<

clean:
	$(RM) *.o
	$(RM) clientBox

vclean: clean	
	$(RM) *~ $(GENERATED).cpp $(GENERATED).h