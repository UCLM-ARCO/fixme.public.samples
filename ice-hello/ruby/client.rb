#!/usr/bin/ruby1.8

require 'Ice'
Ice.loadSlice('../hello.ice')

ic = Ice.initialize(ARGV)
base = ic.stringToProxy(ARGV[0])
prx = UCLM::HelloPrx.checkedCast(base)
prx.puts("Hello, World!")

