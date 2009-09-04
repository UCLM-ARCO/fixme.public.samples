#!/usr/bin/python
# -*- coding: utf-8; mode: python -*-

import gtk

gtk.rc_parse('resource.rc')

win = gtk.Window()
win.connect('destroy', gtk.main_quit)

button = gtk.Button("Example test")
button.set_name('my_button')

win.add(button)

win.show_all()
gtk.main()


