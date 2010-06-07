#!/usr/bin/python2.6
# -*- coding: utf-8; mode: python -*-

import sys

import pycurl

print 'Using PycURL %s version' % pycurl.version

if len(sys.argv) < 2:
    print '''Usage:
\t%s url
''' % sys.argv[0]
    sys.exit(1)

url = sys.argv[1]

c = pycurl.Curl()
c.setopt(pycurl.URL, url)

c.perform()
c.close()
