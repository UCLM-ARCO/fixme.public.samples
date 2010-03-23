# -*- coding:utf-8 -*-

DIRS=hello single_binary

clean:
	$(RM) *~
	@for i in $(DIRS); do \
	$(RM) $$i/*~; \
	done

vclean: clean
	@for i in $(DIRS); do \
	$(RM) -r $$i/CMakeFiles $$i/CMakeCache* $$i/cmake* $$i/Makefile; \
	done

