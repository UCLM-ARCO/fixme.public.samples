
vpath %.cs generated

all: Server.exe Client.exe
Server.exe: Server.cs generated/Hello.cs
Client.exe: Client.cs generated/Hello.cs

clean:
	$(RM) *~ proxy.out
	$(RM) -rf generated/*

run-server: Server.exe
	mono Server.exe --Ice.Config=../config | tee proxy.out

run-client: Client.exe
	mono Client.exe "$(shell head -1 proxy.out)"

%.exe: %.cs
	gmcs -out:$@ -pkg:Ice-3.3 $^

generated/%.cs: %.ice
	slice2cs --output-dir generated $<
