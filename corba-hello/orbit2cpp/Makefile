
PROY=hello
CC=gcc-3.2
CXX=g++-3.2

CFLAGS=-ggdb `pkg-config ORBit-2.0-cpp --cflags`
CXXFLAGS=$(CFLAGS)
LDFLAGS=`pkg-config ORBit-2.0-cpp --libs-only-L`
LDLIBS=-g -O0 `pkg-config ORBit-2.0-cpp --libs-only-l`

CLIENT_C_MODS=$(PROY)-common.c $(PROY)-stubs.c
SERVER_C_MODS=$(CLIENT_C_MODS) $(PROY)-skels.c
CLIENT_CXX_MODS=$(PROY)-cpp-common.cc $(PROY)-cpp-stubs.cc
SERVER_CXX_MODS=$(CLIENT_CXX_MODS) $(PROY)-cpp-skels.cc

CLIENT_OBJ=$(patsubst %, %.o, $(basename $(CLIENT_C_MODS) $(CLIENT_CXX_MODS)))
SERVER_OBJ=$(patsubst %, %.o, $(basename $(SERVER_C_MODS) $(SERVER_CXX_MODS)))

C_HEAD=$(patsubst %.c, %.h, $(SERVER_C_MODS) )
CXX_HEAD=$(patsubst %.cc, %.h, $(SERVER_CXX_MODS))

all:  client server

client: $(CLIENT_OBJ) client.o
	$(CXX) $(LDFLAGS) $(LDLIBS) -o client $^

server: $(SERVER_OBJ) $(PROY)-impl.o server.o
	$(CXX) $(LDFLAGS) $(LDLIBS) -o server $^

$(SERVER_C_MODS): $(PROY).idl
	orbit-idl-2 -l c $<

$(SERVER_CXX_MODS): $(PROY).idl
	orbit-idl-2 -l cpp $<


clean:
	$(RM) $(SERVER_OBJ) 
	$(RM) $(C_HEAD) $(CXX_HEAD)
	$(RM) $(SERVER_C_MODS)
	$(RM) $(SERVER_CXX_MODS)
	$(RM) $(PROY).h $(PROY).c $(PROY)-cpp.h $(PROY)-cpp.cc
	$(RM)  *~ *.o core client server
