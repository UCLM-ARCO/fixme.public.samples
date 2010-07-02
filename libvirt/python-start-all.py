#!/usr/bin/python
# -*- coding:utf-8; mode:python -*-

# startup all domains of a hipervisor

import sys
import libvirt as virt

if len(sys.argv) != 2:
    print 'Usage: ./python-start-all.py URI'
    sys.exit(1)

conn = virt.open(sys.argv[1])

# conn.listDefinedDomains() -> full stopped domains
# conn.listDomainsID()      -> non-full stopped domains

domains = []

for name in conn.listDefinedDomains():
    domains.append(conn.lookupByName(name))

for i in conn.listDomainsID():
    domains.append(conn.lookupByID(i))


for dom in domains:
    state = dom.info()[0]

    if state == virt.VIR_DOMAIN_RUNNING:
        print "Domain '%s' is already running" % dom.name()
        continue

    if state == virt.VIR_DOMAIN_PAUSED:
        print "Domain '%s' is paused. Resuming..." % dom.name()
        dom.resume()
        continue

    # activating domain
    dom.create()
    print "Domain '%s' started!!" % dom.name()

    # destroy reference
#    dom.destroy()

conn.close()

