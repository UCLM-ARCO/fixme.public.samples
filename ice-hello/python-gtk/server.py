#!/usr/bin/python -u
# -*- coding: utf-8 -*-
"A ICE hello-world with GTK GUI"

import sys

import Ice
Ice.loadSlice('../hello.ice')
import UCLM

import gtk, gobject
gobject.threads_init()


class HelloI(UCLM.Hello):
    def puts(self, s, current=None):
        print "Client say: ", s
        gobject.idle_add(gui.textbuffer.insert_at_cursor, s+'\n')


class Gui:
    def __init__(self):
        window = gtk.Window(gtk.WINDOW_TOPLEVEL)
        window.resize(200,100)
        textview = gtk.TextView()
        window.add(textview)
        window.show_all()
        window.connect('destroy', gtk.main_quit)
        self.textbuffer = textview.get_buffer()


class Server(Ice.Application):
    def run(self, argv):

        ic = self.communicator()
        servant = HelloI()

        adapter = ic.createObjectAdapter("Server")
        prx = adapter.add(servant, ic.stringToIdentity("Hello"))
        adapter.activate()

        print prx

        self.callbackOnInterrupt()
        gtk.main()
        ic.shutdown()
        return 0

    def interruptCallback(self, args):
        gobject.idle_add(gtk.main_quit)


gui = Gui()
sys.exit(Server().main(sys.argv))

