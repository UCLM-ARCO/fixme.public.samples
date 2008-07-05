CXXFLAGS=-I/usr/include/python2.4
LDFLAGS=-shared -lboost_python

Hello.so: hello.o hello_wrapper.o
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	$(RM) Hello.so *.o *~