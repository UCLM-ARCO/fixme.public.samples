#!/usr/bin/python
# -*- mode:python; coding:utf-8; tab-width:4 -*-

import sys
import PAM

if len(sys.argv) != 2:
    print "Usage: %s service" % __file__
    sys.exit(1)

service = sys.argv[1]

auth = PAM.pam()
auth.start(service)

try:
    auth.authenticate()
    print "OK"
except Exception,e:
    print "FAIL", e


