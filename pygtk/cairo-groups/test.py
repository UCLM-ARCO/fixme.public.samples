#!/usr/bin/env python
# -*- mode: python; coding: utf-8 -*-

import gtk
import cairo

class Test:
    def __init__(self):
        mw = gtk.Window(gtk.WINDOW_TOPLEVEL)
        mw.connect("delete-event", gtk.main_quit)
        mw.set_size_request(400, 400)

        da = gtk.DrawingArea()
        da.modify_bg(gtk.STATE_NORMAL, gtk.gdk.Color(0xffff, 0xffff, 0xffff))
        da.connect("expose_event", self.on_expose)
        mw.add(da)

        # Source image, loaded as a pixbuf
        self._img = gtk.gdk.pixbuf_new_from_file("photos.svg")

        mw.show_all()


    def on_expose(self, widget, event):
        cr = widget.window.cairo_create()

        # Normal image
        cr.set_source_pixbuf(self._img, 175, 50)
        cr.paint()

        # Black shape of same image
        cr.push_group()
        cr.set_source_pixbuf(self._img, 175, 150)
        cr.paint()
        src = cr.pop_group()
        cr.set_source_rgb(0, 0, 0)
        cr.mask(src)

        # Blue shape of same image, with alpha
        cr.set_source_pixbuf(self._img, 175, 250)
        cr.paint()

        cr.push_group()
        cr.set_source_pixbuf(self._img, 175, 250)
        cr.paint()
        src = cr.pop_group()
        cr.set_source_rgba(.5, .5, 1, .4)
        cr.mask(src)




if __name__ == "__main__":
    t = Test()
    try:
        gtk.main()
    except KeyboardInterrupt:
        gtk.main_quit()
