all:

clean:
	$(RM) proxy.out *~

run-client: client.rb
	ruby1.8 client.rb "$(shell head -1 proxy.out)"

