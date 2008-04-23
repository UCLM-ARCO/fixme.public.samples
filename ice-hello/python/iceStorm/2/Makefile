

PARSER=slice2py
OBJ=hello.ice
RESULT=hello_ice.py UCLM db *.pyc
RM=rm -vfr

all:
	$(RM) ./db
	mkdir ./db
	$(PARSER) $(OBJ)

.PHONY: clean
clean:
	$(RM) $(RESULT) *~