#!/usr/bin/python
# -*- coding: utf-8 -*-

import gtk
from gladewrapper import GladeWrapper

class Application(GladeWrapper):

    def __init__(self):
        GladeWrapper.__init__(self, 'gui.glade')

    def on_button_clicked(self, button):
        self.wg_entry.set_text('¡Ejemplo mínimo!')

    def on_window_delete_event(self, *args):
        gtk.main_quit()

    def run(self):
        gtk.main()


Application().run()
