#!/usr/bin/python
# -*- coding: utf-8 -*-

import gtk, gladeutil

class Application(gladeutil.Wrapper):
    quit = gtk.main_quit

    def on_button_clicked(self, button):
        self.wg_entry.set_text('Minimal sample!')


app = Application('gui.glade')
gtk.main()
