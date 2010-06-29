
CXX=g++
CXXFLAGS = -I.
LDLIBS = -lIce -lIceUtil -lIceStorm

SLICE = hello

all: publisher subscriber

publisher: publisher.o $(SLICE).o
subscriber: subscriber.o $(SLICE).o

publisher.cpp subscriber.cpp: $(SLICE).h $(SLICE).cpp

init:
	@if ! [ -d db ]; then mkdir db; fi

vpath %.ice ../

%.h %.cpp: %.ice
	slice2cpp $<

clean:
	$(RM) publisher subscriber *.o *~
	$(RM) -r db $(SLICE).*


run-subscriber: init subscriber /usr/bin/icebox /usr/bin/icestormadmin
	icebox --Ice.Config=icebox.config &
	sleep 5
	icestormadmin --Ice.Config=icestorm.config -e "create HelloTopic"
	./subscriber --Ice.Config=icestorm.config

run-publisher: publisher
	./publisher --Ice.Config=icestorm.config

