PROY=hello
JAVAC=javac
JFLAGS=

vpath %.java HelloModule

IDL_MODULE_NAME=HelloModule
SERVER_FILES=$(PROY)Operations $(PROY)POA
CLIENT_FILES=$(PROY)Helper _$(PROY)Stub $(PROY)Holder
GENERATED=$(PROY) $(SERVER_FILES) $(CLIENT_FILES)

all: $(PROY).java $(PROY)Server.class $(PROY)Client.class

$(addsuffix .java, $(GENERATED)): $(PROY).idl
	idlj -fall $<

helloServer.class: helloServer.java $(addsuffix .class, $(PROY) $(SERVER_FILES))
helloClient.class: helloClient.java $(addsuffix .class, $(PROY) $(CLIENT_FILES))

%.class: %.java
	$(JAVAC) $(JFLAGS) $<

clean:
	$(RM) -rf $(IDL_MODULE_NAME)
	$(RM) *.class *~
	$(RM) $(addsuffix .java, $(GENERATED))