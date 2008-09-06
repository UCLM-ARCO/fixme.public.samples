#!/usr/bin/python
# -*- coding: utf-8 -*-

import gtk
from gladeutil import Wrapper

class Application(Wrapper):

    def __init__(self):
        Wrapper.__init__(self, 'gui.glade')
        self.wg_window.connect('destroy', gtk.main_quit)

    def on_button_clicked(self, button):
        self.wg_entry.set_text('Minimal sample!')


app = Application()
gtk.main()
