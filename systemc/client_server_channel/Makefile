# Paths especificos
#################################################

TARGET_ARCH     = linux
PATH_OSCI = /home/miguel/Software/gspm/OSCI
SYSTEMC_HOME = $(PATH_OSCI)/systemc/2.2/gcc4.0
TLM_HOME = $(PATH_OSCI)/tlm/1.0

#################################################
SYSTEMC_INC_DIR  = $(SYSTEMC_HOME)/include
SYSTEMC_LIB_DIR  = $(SYSTEMC_HOME)/lib-$(TARGET_ARCH)
TLM_INC_DIR      = $(TLM_HOME)/include

GXX = g++
GCC = gcc
LD  = g++
FLAGS = -g -Werror -Wno-long-long -Wno-deprecated \
	-I$(SYSTEMC_INC_DIR) -I$(TLM_INC_DIR)

LDFLAGS = -L$(SYSTEMC_LIB_DIR) -lsystemc -L$(SYSTEMC_LIB_DIR) \
	-L$(SYSTEMC_LIB_DIR) -lsystemc

OBJ_NAME = run

INCDIR =    -I.

SRCDIR          = .
SRCCOMMONDIR    = .

CFLAGS = $(FLAGS) $(INCDIR)

OBJS = main.o


.PHONY: clean all check

all: $(OBJ_NAME)

$(OBJ_NAME): $(OBJS)
	$(LD) -o $@ $(OBJS) $(LDFLAGS)

main.o: $(SRCDIR)/main.cc *.h
	$(GXX) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.log $(OBJ_NAME) *~


