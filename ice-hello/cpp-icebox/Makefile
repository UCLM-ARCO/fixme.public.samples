
CXX=g++
CXXFLAGS=-I.
LDLIBS=-lIce -lIceUtil -lIceBox


GENERATED = hello

all: $(GENERATED).cpp libHelloService.so client

client: hello.o client.o
	$(CXX) $(LDLIBS) $^ -o $@

libHelloService.so: HelloService.o $(GENERATED).o $(GENERATED)I.o
	$(CXX) $(LDLIBS) -shared -o $@ $^


$(GENERATED): $(GENERATED).cpp

$(GENERATED).o: $(GENERATED).cpp

$(GENERATED).cpp: $(GENERATED).ice
	slice2cpp $<

install:
	cp libHelloService.so /usr/lib/

unistall:
	$(RM) /usr/lilb/libHelloService.so

clean:
	$(RM) *.o $(GENERATED).h $(GENERATED).cpp
	$(RM) libHelloService.so client

vclean: clean
	$(RM) *~ $(GENERATED).cpp $(GENERATED).h

run-server: all
	LD_LIBRARY_PATH=. icebox --Ice.Config=icebox.cfg | tee proxy.out

run-client: all
	./client	"$(shell head -1 proxy.out)"

