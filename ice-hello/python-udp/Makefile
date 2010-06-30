
all:

clean:
	$(RM) *~ proxy.out


run-server-udp:
	./server.py Server.udp --Ice.Config=../config | tee proxy.out

run-server-mcast:
	./server.py Server.mcast --Ice.Config=../config | tee proxy.out


run-client:
	./client.py "$(shell head -1 proxy.out)"
