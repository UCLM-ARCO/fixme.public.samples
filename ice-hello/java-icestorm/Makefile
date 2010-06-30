
TARGET=publisher.class subscriber.class

all: UCLM $(TARGET)

%.class: %.java
	javac -Xlint:unchecked -classpath /usr/share/java/Ice.jar:. $<

UCLM: ../hello.ice
	slice2java $<

clean:
	$(RM) *.class
	$(RM) *~
	$(RM) -r db
	$(RM) -r UCLM
