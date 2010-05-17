#!/usr/bin/python
import math

import gtk
import cairo
import pango
import pangocairo


WIDTH, HEIGHT = 256, 256

surface = cairo.ImageSurface (cairo.FORMAT_ARGB32, WIDTH, HEIGHT)
ctx = cairo.Context(surface)

cr = pangocairo.CairoContext(ctx)
layout = cr.create_layout()
cr.set_source_rgb(0, 0, 0)
cr.show_layout(layout)

desc = pango.FontDescription("helvetica bold 10")
layout.set_font_description(desc)
layout.set_text("hola")


da = gtk.DrawingArea()
da.draw(ctx)

w = gtk.Window()
w.add(da)

w.show_all()

gtk.main()
