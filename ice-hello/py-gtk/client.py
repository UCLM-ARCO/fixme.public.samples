#!/usr/bin/python -u
# -*- coding: utf-8 -*-

import sys, Ice
Ice.loadSlice('../hello.ice')
import UCLM

import gtk

class Gui:
    def __init__(self, app):
        window = gtk.Window(gtk.WINDOW_TOPLEVEL)
        window.resize(200,100)
        button = gtk.Button("click here")
        window.add(button)
        window.show_all()
        button.connect('clicked', self.on_button_clicked)
        window.connect('destroy', gtk.main_quit)

    def on_button_clicked(self, wd):
        app.send_hello()


class Client (Ice.Application):
    def run(self, argv):
        base = self.communicator().stringToProxy(argv[1])
        self.prx = UCLM.HelloPrx.checkedCast(base)
        if not self.prx:
            raise RuntimeError("Invalid proxy")

        gtk.main()

    def send_hello(self):
        self.prx.puts("Hello World!")


app = Client()
gui = Gui(app)
sys.exit(app.main(sys.argv))
