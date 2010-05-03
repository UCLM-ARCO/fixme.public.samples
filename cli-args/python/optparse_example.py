#!/usr/bin/python

import optparse
import sys


def printpi(option, opt, value, parser):
    print "option:", option
    print "opt:   ", opt
    print "value: ", value

    print ""
    print value**2
    print ""
    return



parser = optparse.OptionParser()

# This is an option, with an argument
parser.add_option("-f", "--source-file",
                  dest="source",
                  type="string",
                  help="Destination file")

# This is a flag
parser.add_option("-b",
                  action='store_true',
                  dest='binary',
                  default=False,
                  help="Treat the source file as binary")

parser.add_option("-p", "--pi",
                  action='callback',
                  callback=printpi,
                  type="int",
                  help="Print the square of n")

try:
    options, arguments = parser.parse_args()

    print 'OPTIONS:'
    print 'source =', options.source
    print 'binary =', options.binary

    print '\nARGS:', arguments

except optparse.OptionConflictError, err:
    print err

