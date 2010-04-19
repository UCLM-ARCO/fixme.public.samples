#!/usr/bin/python
"A ICE hello-world with GTK GUI"

import sys

import Ice
Ice.loadSlice('hello.ice')
import UCLM

import gtk, gobject
gtk.threads_init()


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
        window.connect('destroy', self.main_quit)
        self.textbuffer = textview.get_buffer()

    def main_quit(self, obj):
        gtk.main_quit()


class Server(Ice.Application):
    def run(self, argv):

        # 1) Creamos un adaptador de objetos.
        adapter = self.communicator().createObjectAdapter("Servidor")

        # 2) Instanciamos el objeto HelloI.
        obj = HelloI()

        # 3) Informamos al adaptador acerca de un nuevo sirviente "Hello"
        prx = adapter.add(obj, self.communicator().stringToIdentity("Hello"))

        # 4) Activacion del Adaptador.
        adapter.activate()

        print self.communicator().proxyToString(prx)

        self.shutdownOnInterrupt()

        gtk.main()
        #self.communicator().waitForShutdown()


gui = Gui()
Server().main(sys.argv, 'config')

