IFACE=hello.ice
TARGET=publisher.class subscriber.class

all: $(IFACE) db UCLM $(TARGET)

%.class: %.java
	javac -classpath /usr/share/java/Ice.jar:. $<

$(IFACE):
	ln -s ../../hello.ice .

db:
	mkdir db

UCLM:
	slice2java $(IFACE)

clean:
	$(RM) *.class
	$(RM) *~
	$(RM) db/*
	rmdir db
	$(RM) UCLM/*
	rmdir UCLM
