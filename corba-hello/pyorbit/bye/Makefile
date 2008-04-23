

CFLAGS=-fPIC `pkg-config --cflags ORBit-2.0`
LDFLAGS=-shared `pkg-config --libs ORBit-2.0`

IDLC=orbit-idl-2 
IDLFLAGS=--imodule

all: bye_module.so

%_module.so: %-imodule.o
	$(CC) -o $@ $^ $(LDFLAGS)

%-imodule.c: %.idl
	$(IDLC) $(IDLFLAGS) $<

clean:
	$(RM) *.c *.h *.o *.so *~ IOR
