CFLAGS+=-I. -I/usr/include -I/usr/local/include
CFLAGS+=-I./

LDLIBS+=-L/usr/lib -L/usr/local/lib -L. \
	-lIce -lIceUtil 

CXXFLAGS+=$(CFLAGS)

CC=gcc
CXX=g++

GENERATED = hello

all: $(GENERATED).cpp libHelloService.so


libHelloService.so: HelloService.o $(GENERATED).o $(GENERATED)I.o
	$(CC) $(LDLIBS) -shared -o $@ $^
	$(MAKE) -C client/


$(GENERATED): $(GENERATED).cpp

$(GENERATED).o: $(GENERATED).cpp

$(GENERATED).cpp: $(GENERATED).ice
	slice2cpp $<

#$(GENERATED).ice: ../../slice/Senda.ice
#	ln -s $< $@

install:
	cp libHelloService.so /usr/lib/

unistall:
	$(RM) /usr/lilb/libHelloService.so

clean:
	$(RM) *.o
	$(RM) libHelloService.so
	$(MAKE) -C ./client vclean	

vclean: clean
	$(RM) *~ $(GENERATED).cpp $(GENERATED).h


