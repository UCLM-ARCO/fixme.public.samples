# -*- mode: makefile-gmake; coding: utf-8 -*-

SUBDIRS = $(shell ls -d */)
SUBDIRS = cpp cpp-icestorm cpp-facets cpp-freeze

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
