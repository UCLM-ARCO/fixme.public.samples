
CXX=g++
CXXFLAGS = -I.
LDLIBS = -lIce -lIceUtil -lIceStorm

SLICE = hello

all: publisher subscriber

publisher: publisher.o $(SLICE).o
subscriber: subscriber.o $(SLICE).o

publisher.cpp subscriber.cpp: $(SLICE).h $(SLICE).cpp

vpath %.ice ../

%.h %.cpp: %.ice
	slice2cpp $<

clean:
	$(RM) publisher subscriber *.o *~
	$(RM) -r db $(SLICE).*


run-subscriber: start subscriber /usr/bin/icebox /usr/bin/icestormadmin
	./subscriber --Ice.Config=icestorm.config

run-publisher: publisher
	./publisher --Ice.Config=icestorm.config

start:
	@if ! [ -d db ]; then mkdir db; fi
	icebox --Ice.Config=icebox.config &
	sleep 3
	icestormadmin --Ice.Config=icestorm.config -e "create HelloTopic"

stop:
	icestormadmin --Ice.Config=icestorm.config -e "destroy HelloTopic"
	killall icebox
