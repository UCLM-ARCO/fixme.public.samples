#!/usr/bin/python2.6
# -*- coding: utf-8; mode: python -*-

import sys

import pycurl
import urllib

print 'Using PycURL %s version' % pycurl.version

if len(sys.argv) < 3:
    print '''Usage:
\t%s url cookie_file
''' % sys.argv[0]
    sys.exit(1)

url = sys.argv[1]
cookie_file = sys.argv[2]

c = pycurl.Curl()
c.setopt(pycurl.URL, url)
c.setopt(pycurl.COOKIEFILE, cookie_file)

c.perform()
c.close()
