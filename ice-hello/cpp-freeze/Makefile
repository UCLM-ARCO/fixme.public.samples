# -*- mode: gnumakefile; coding: utf-8 -*-

# Files and Paths
DBDIR    = storage
NISRC    = Message.ice
PISRC    = PersistentMessage.ice

CLIENT   = client
NSERVER  = server
PSERVER  = persistentServer

# Tools
SLICE2CPP = slice2cpp
MKDIR     = mkdir -p

# Config and flags
CXXFLAGS = -Wall -g -ansi -I.
LDFLAGS  = -lFreeze -lIce

# Targets
all: $(CLIENT) $(NSERVER) $(PSERVER)

Ice:

$(NISRC:.ice=.o): $(NISRC)
	$(SLICE2CPP) $^
	$(CXX) -c $(CXXFLAGS) -o $@ $(@:.o=.cpp)

$(PISRC:.ice=.o): $(PISRC)
	$(SLICE2CPP) $^
	$(CXX) -c $(CXXFLAGS) -o $@ $(@:.o=.cpp)


$(CLIENT): $(NISRC:.ice=.o) $(CLIENT:=.o)
	$(CXX) $(LDFLAGS) -o $@ $^

$(NSERVER): $(NISRC:.ice=.o) $(NISRC:.ice=I.o) $(NSERVER:=.o)
	$(CXX) $(LDFLAGS) -o $@ $^

$(PSERVER): $(NISRC:.ice=.o) $(PISRC:.ice=.o) $(PISRC:.ice=I.o) $(PSERVER:=.o)
	$(CXX) $(LDFLAGS) -o $@ $^
	$(MKDIR) $(DBDIR)


.PHONY: clean
clean:
	$(RM) *.o *~ \#*\#
	$(RM) $(NISRC:.ice=.cpp) $(NISRC:.ice=.h) $(PISRC:.ice=.cpp) $(PISRC:.ice=.h)
	$(RM) $(NSERVER) $(PSERVER) $(CLIENT)
	$(RM) $(DBDIR) -fr
