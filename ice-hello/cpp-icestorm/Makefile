CXX=g++

GENERATED = hello

TARGETS	= publisher subscriber

POBJS	= publisher.o
SOBJS	= subscriber.o $(GENERATED)I.o

SRCS	= $(OBJS:.o=.cpp) $(POBJS:.o=.cpp) $(SOBJS:.o=.cpp)
OBJS	= interface.o


all: init $(GENERATED).cpp publisher subscriber

init: 
	@if ! [ -d db ]; then mkdir db; fi 
	@if ! [ -f hello.ice ]; then ln -s ../../hello.ice .; fi

$(GENERATED).cpp: hello.ice
	slice2cpp hello.ice


CXXFLAGS = -I.
LDLIBS = -L/usr/lib -lIce -lIceUtil -lIceStorm

publisher.o: publisher.cpp hello.h
publisher: publisher.o hello.o

subscriber.o: subscriber.cpp hello.h
subscriber: subscriber.o hello.o helloI.o

clean:
	$(RM) *.o

vclean: clean
	$(RM) *~ $(GENERATED).cpp $(GENERATED).h
	$(RM) publisher subscriber
	$(RM) -r db hello.ice