CFLAGS+=-I. -I/usr/include -I/usr/local/include
CFLAGS+=-I./ $(PTCXXFLAGS) $(ICECXXFLAGS)

LDLIBS+=-L/usr/lib -L/usr/local/lib -L. \
	-lIce -lIceUtil -IceStorm $(PTLDLIBS) $(ICELDLIBS)

CXXFLAGS+=$(CFLAGS)

PTCXXFLAGS=	`ptlib-config --ccflags` -fexceptions
PTLDLIBS=	`ptlib-config --libs` -fexceptions

ICECXXFLAGS=
ICELDLIBS=	-lIceStorm -lIce -lIceUtil -lpthread -ldl

CC=gcc
CXX=g++

GENERATED = hello

PUBLISHER	= publisher

all: $(GENERATED).cpp libHelloService.so Publisher


libHelloService.so: HelloService.o $(GENERATED).o $(GENERATED)I.o
	$(CC) $(LDLIBS) -shared -o $@ $^


$(GENERATED): $(GENERATED).cpp

$(GENERATED).o: $(GENERATED).cpp

$(GENERATED).cpp: $(GENERATED).ice
	slice2cpp $<

Publisher.o: Publisher.cpp hello.h
Publisher: Publisher.o hello.o

#$(GENERATED).ice: ../../slice/Senda.ice
#	ln -s $< $@

install:
	cp libHelloService.so /usr/lib/

unistall:
	$(RM) /usr/lib/libHelloService.so

clean:
	$(RM) *.o
	$(RM) libHelloService.so Publisher

vclean: clean
	$(RM) *~ $(GENERATED).cpp $(GENERATED).h


