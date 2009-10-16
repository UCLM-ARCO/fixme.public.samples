#!/usr/bin/python

import gtk, time

def act(entry, *args):
    text = entry.get_text().encode("latin-1", "strict")
#    fd = open('hola%s' % time.time(), 'w')
#    fd.write(text)
#    fd.close()


e = gtk.Entry()
e.connect("activate", act)
w = gtk.Window()
w.add(e)
w.show_all()

gtk.main()
