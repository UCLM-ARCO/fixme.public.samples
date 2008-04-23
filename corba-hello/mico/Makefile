
LD=mico-ld
IDL=idl
LDLIBS=-lmico2.3.10 `pkg-config gthread --libs`

all: client server

server: hello.o server.o hello_skel.o
	$(LD) $(LDFLAGS) $(LDLIBS) $^ -o $@

client: hello.o client.o
	$(LD) $(LDFLAGS) $(LDLIBS) $^ -o $@ 


hello.h hello.cc hello_skel.cc: hello.idl
	$(IDL) --c++-impl --c++-skel $<

clean:
	$(RM) hello.cc hello.h hello.ref hello_skel.cc 
	$(RM) *.o core client server *~ 
