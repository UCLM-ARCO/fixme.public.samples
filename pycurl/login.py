#!/usr/bin/python2.6
# -*- coding: utf-8; mode: python -*-

import sys

import pycurl
import urllib

print 'Using PycURL %s version' % pycurl.version

if len(sys.argv) < 4:
    print '''Usage:
\t%s url user pass [cookie_file_name]

If no cookie file name is given, it will write the cookie on /tmp/cookie.txt
''' % sys.argv[0]
    sys.exit(1)

url  = sys.argv[1]
user = sys.argv[2]
pwd  = sys.argv[3]

try:
    cookie_file = sys.argv[4]

except IndexError:
    cookie_file = '/tmp/cookie.txt'

post_values = {'name': user,
               'pass': pwd,
               'form_id': 'user_login'}

c = pycurl.Curl()
c.setopt(pycurl.URL, url)
c.setopt(pycurl.POSTFIELDS, urllib.urlencode(post_values))
c.setopt(pycurl.COOKIEJAR, cookie_file)

c.perform()
c.close()
