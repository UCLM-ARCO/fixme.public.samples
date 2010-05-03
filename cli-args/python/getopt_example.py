#!/usr/bin/python

import getopt
import sys

# This is the list of supported short options and flags. Short options
# (i.e. -f filename) have a colon (:) afterwards; flags don't
SHORTOPTS = "f:bh"

# This is the list of supported long options. Those which need an
# argument (--file-name file.txt) must have a trailing '=' symbol
ACTIONS  = ['help', 'source-file=']

exitcode = 0

useropts = []

try:
    options, arguments = getopt.getopt(sys.argv[1:], SHORTOPTS, ACTIONS)
    print 'OPTIONS:'
    for option in options:
        print '\t%s%s' % (option[0].ljust(3), option[1].ljust(15))

    print 'ARGS:'
    for arg in arguments:
        print '\t',arg

except getopt.GetoptError, err:
    print err





