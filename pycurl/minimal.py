#!/usr/bin/python2.6
# -*- coding: utf-8; mode: python -*-

import sys

import pycurl

print 'Using PycURL %s version' % pycurl.version

if len(sys.argv) < 2:
    print "Usage:\t%s url\n" % __file__
    sys.exit(1)

c = pycurl.Curl()
c.setopt(pycurl.URL, sys.argv[1])

c.perform()
c.close()
