
vpath %.java generated/UCLM
vpath %.class ../bin/java
vpath %.class ../bin/java/UCLM

all: Server.class Client.class
Server.class: Server.java HelloI.java Hello.java
Client.class: Client.java Hello.java

install: all

clean:
	$(RM) proxy.out *~
	$(RM) -rf generated/*
	$(RM) -rf ../bin/*

%.java: %.ice
	slice2java --output-dir generated $<

%.class: %.java
	install -d ../bin/java
	javac -source 1.5 -classpath .:generated:../bin:/usr/share/java/Ice.jar -d ../bin/java $<

run-server: Server.class
	java -classpath ../bin/java:/usr/share/java/Ice.jar \
		Server --Ice.Config=hello.cfg | tee proxy.out

run-client: Client.class
	java -classpath ../bin/java:/usr/share/java/Ice.jar \
	    Client "$(shell head -1 proxy.out)"
