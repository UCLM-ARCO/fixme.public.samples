# -*- coding: utf-8 -*-

import cairo
import gtk
import pango

class myApp:
    def __init__(self):
        mw = gtk.Window(gtk.WINDOW_TOPLEVEL)
        mw.connect("delete_event", gtk.main_quit)

        da = gtk.DrawingArea()
        da.connect("expose_event", self.expose)

        mw.add(da)
        mw.set_size_request(200, 50)
        mw.show_all()


    def expose(self, da, event):
        cr = da.window.cairo_create()

        layout = cr.create_layout()
        desc = pango.FontDescription("helvetica bold 20")
        layout.set_font_description(desc)

        layout.set_text("你好世界!")

        cr.move_to(35, 5)
        cr.show_layout(layout)


if __name__ == "__main__":
    try:
        app = myApp()
        gtk.main()
    except KeyboardInterrupt:
        pass

