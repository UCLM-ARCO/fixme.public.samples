# -*- mode: makefile-gmake; coding: utf-8 -*-

SUBDIRS = $(shell ls -d */)
SUBDIRS = \
	cpp cpp-icestorm cpp-facets cpp-freeze cpp-icebox cpp-glacier2 \
	python python-ping python-udp python-icestorm

all:     RULE = all
install: RULE = install
clean:   RULE = clean

all clean install: subdirs

check: all
	atheist .

clean:
	$(RM) *~


.PHONY: subdirs $(SUBDIRS)
subdirs: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ $(RULE)
