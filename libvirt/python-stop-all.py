#!/usr/bin/python
# -*- coding:utf-8; mode:python -*-

# shutdown all domains of a hipervisor

import sys
import libvirt as virt

if len(sys.argv) != 2:
    print 'Usage: ./python-stop-all.py URI'
    sys.exit(1)

conn = virt.open(sys.argv[1])

domains = []

for name in conn.listDefinedDomains():
    domains.append(conn.lookupByName(name))

for i in conn.listDomainsID():
    domains.append(conn.lookupByID(i))


# It is also possible to shutdown every domains by using
# dom.destroy()

for dom in domains:
    state = dom.info()[0]

    if state in [virt.VIR_DOMAIN_SHUTDOWN, virt.VIR_DOMAIN_SHUTOFF]:
        print "Domain '%s' is already stopped" % dom.name()
        continue

    if state == virt.VIR_DOMAIN_RUNNING:
        print "Domain '%s' stopped!!" % dom.name()
    elif state == virt.VIR_DOMAIN_PAUSED:
        print "Domain '%s' is paused. Stopping..." % dom.name()
    dom.shutdown()

    # destroy reference
    dom.destroy()

conn.close()

