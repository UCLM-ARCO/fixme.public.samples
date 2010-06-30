CXX=g++

GENERATED = hello

TARGETS	= publisher subscriber

POBJS	= publisher.o
SOBJS	= subscriber.o $(GENERATED)I.o

SRCS	= $(OBJS:.o=.cpp) $(POBJS:.o=.cpp) $(SOBJS:.o=.cpp)
OBJS	= interface.o

all: $(GENERATED).cpp publisher subscriber


%.cpp: %.ice
	slice2cpp $<

CXXFLAGS = -I.
LDLIBS = -L/usr/lib -lIce -lIceUtil -lIceStorm

publisher.o: publisher.cpp hello.h
publisher: publisher.o hello.o

subscriber.o: subscriber.cpp hello.h
subscriber: subscriber.o hello.o helloI.o

clean:
	$(RM) *.o
	$(RM) *~ $(GENERATED).cpp $(GENERATED).h
	$(RM) publisher subscriber
