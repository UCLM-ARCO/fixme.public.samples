#!/usr/bin/python
# -*- coding: utf-8 -*-

import gtk
from gladewrapper import GladeWrapper

class Application(GladeWrapper):

    def __init__(self):
        GladeWrapper.__init__(self, 'gui.glade')
        self.wg_window.connect('destroy', gtk.main_quit)

    def on_button_clicked(self, button):
        self.wg_entry.set_text('¡Ejemplo mínimo!')


app = Application()
gtk.main()
