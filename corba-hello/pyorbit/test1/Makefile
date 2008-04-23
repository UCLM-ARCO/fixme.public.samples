

TARGET=hello_module.so mico_server mico_client

all: $(TARGET)


hello_module.so: CFLAGS=-fPIC `pkg-config --cflags ORBit-2.0`
hello_module.so: hello-imodule.o
	gcc -o $@ $^ -shared `pkg-config --libs ORBit-2.0`

hello-imodule.c: hello.idl
	orbit-idl-2 --imodule $<


mico_server: hello.o mico_server.o hello_skel.o
	mico-ld -lmico2.3.11 `pkg-config gthread --libs` $^ -o $@

mico_client:  hello.o mico_client.o
	mico-ld -lmico2.3.11 `pkg-config gthread --libs` $^ -o $@ 


hello.hh hello.cc hello_skel.cc: hello.idl
	idl --c++-impl --c++-skel --hh-suffix=hh $<

clean:
	$(RM) *.c *.h *.o *.so *~ *.ior
	$(RM) hello.cc hello.hh hello_skel.cc hello_impl.*
	$(RM) core.* $(TARGET) *~ 
