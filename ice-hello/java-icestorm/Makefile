IFACE=hello.ice
TARGET=publisher.class subscriber.class

all: $(IFACE) UCLM $(TARGET)

%.class: %.java
	javac -Xlint:unchecked -classpath /usr/share/java/Ice.jar:. $<

$(IFACE):
	ln -s ../../hello.ice .

UCLM:
	slice2java $(IFACE)

clean:
	$(RM) *.class
	$(RM) *~
	$(RM) -r db
	$(RM) -r UCLM
