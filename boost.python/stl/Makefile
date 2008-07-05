CXXFLAGS=-I/usr/include/python2.4 -I/usr/include/boost
LDFLAGS=--fPIC -shared -lboost_python -lpython2.4

MODULE=Control.so

all: $(MODULE)

$(MODULE): control_wrapper.o
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	$(RM) $(MODULE) *.o *~ \#*